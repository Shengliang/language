
// References:
// A simple and effective algorithm for virtual memory
// infolab.stanford.edu/~manku/quals/zpapers/81-wsclock.pdf.gz
// http://cs.winona.edu/Francioni/cs405/wsclock.html
// g++ -std=c++11  vm_wsclock.cpp  

#include<algorithm>
#include<atomic>
#include<queue>
#include<string>
#include<vector>
#include<iostream>
#include<map>

#include <unistd.h> // pid_t getpid(void);
#include<time.h>    // time(NULL)
using namespace std;

#define HIT  0
#define MISS 1

typedef time_t vt_type;
#define THETA_DEFAULT_VALUE 1000 
#define NUM_PAGES 1024
//#define NUM_PAGES 16

//#define NUM_PAGES 1024*1024
// #define MS 16
// #define MS 64
// #define MS 512
#define MS 128

class VM
{
    std::vector<uint64_t> m_clock;
    std::vector<vt_type> m_last_reference_time;
    std::vector<char> m_use_bit;
    std::vector<char> m_dirty_bit;
    std::vector<pid_t> m_process;
    std::atomic<uint32_t> m_hand;
    std::map<pid_t, bool> m_active;
    std::map<uint64_t, uint32_t> m_vpns;
    uint32_t m_page_offset;
    uint32_t m_size;
    vt_type m_theta;
    std::queue<uint64_t> m_clean_request_que;
    uint64_t m_count[2];
public:
    uint64_t get_hit_count() const { return m_count[HIT];}
    uint64_t get_miss_count() const { return m_count[MISS];}
    uint32_t get_vpns() const { return m_vpns.size(); }
    /* 16KB Page (14-bit page offset)
     * 16GB Page Buffer Memory (1M Pages)
     */
    VM(uint32_t size = NUM_PAGES, uint32_t page_offset = 14, uint64_t theta = THETA_DEFAULT_VALUE)
	: m_page_offset(page_offset), m_size(size), m_theta(theta) {
	vt_type vt = time(NULL);
	m_clock.resize(size, 0LL);
	m_last_reference_time.resize(size, vt);
	m_use_bit.resize(size, 0);
	m_dirty_bit.resize(size, 0);
	m_process.resize(size, 0);
	m_hand = 0;
    } 

    void clean_process() {
      if (!m_clean_request_que.empty()) {
	uint32_t hand = m_clean_request_que.front();
	uint32_t vpn = m_clock[hand];
	// flush page(vpn)
	m_clean_request_que.pop();
	char old_dirty_bit = 0;
	char new_dirty_bit = 0;
	// __ATOMIC_RELAXED, __ATOMIC_SEQ_CST, __ATOMIC_ACQUIRE, __ATOMIC_RELEASE, and __ATOMIC_ACQ_REL.
	__atomic_exchange(&m_dirty_bit[hand], &new_dirty_bit, &old_dirty_bit, __ATOMIC_ACQUIRE);
      }
    }

    vt_type get_task_virtual_time() {
	return time(NULL);
    }

    bool is_process_active(pid_t pid) {
	return m_active[pid];
    }
    void set_process_active(pid_t pid) {
	m_active[pid] = true;
    }
    void replace(uint64_t vpn) {
	for(;;) {
		//1. Advance clock pointr
		++m_hand;
		m_hand = m_hand % m_size;

		//2. Test and clear use-bit
		char new_use_bit = 0;
		char old_use_bit = 0;

		// It stores the contents of *val into *ptr.
		// The original value of *ptr is copied into *ret.
		// void __atomic_exchange (type *ptr, type *val, type *ret, int memorder)
		__atomic_exchange(&m_use_bit[m_hand], &new_use_bit, &old_use_bit, __ATOMIC_ACQUIRE);
        	vt_type vt = get_task_virtual_time();
#if 0
		cout << "m_hand:" << m_hand << " delta t: " << vt << " - " << m_last_reference_time[m_hand] 
		                    << " = " << vt - m_last_reference_time[m_hand] << endl;
#endif
		if (old_use_bit) {
			m_last_reference_time[m_hand] = vt;
			if (is_process_active(m_process[m_hand])) {
			   continue;
			}
		}
		else if ((vt - m_last_reference_time[m_hand]) < m_theta) {
			if (is_process_active(m_process[m_hand])) {
			   continue;
			}
		}

		if (m_dirty_bit[m_hand]) {
			// schedule page for cleaning
			m_clean_request_que.push(m_hand);
			continue;
		}

		// replace page
		uint64_t old_vpn = m_clock[m_hand];
		if (old_vpn) {
			cout << "erase: " << hex << vpn << endl;
			m_vpns.erase(old_vpn);
		}
		m_vpns[vpn] = m_hand;
		m_clock[m_hand] = vpn;
		cout << hex << vpn << endl;
		break;
	}
    }

    void access(void* ptr) {
	uint64_t vpn = ((uint64_t) ptr) >> m_page_offset;
	pid_t pid = getpid();
	set_process_active(pid);
	const auto & search = m_vpns.find(vpn);
	if (search == m_vpns.end()) {
    		replace(vpn);
		++m_count[MISS];
	} else {
        	vt_type vt = get_task_virtual_time() ;
		uint32_t m_hand = search->second;
		m_use_bit[m_hand] = 1;
		m_last_reference_time[m_hand] = vt;
		// cout << "LR(" << m_hand << ") = vpn:" << vpn << "@" << vt << endl;
		++m_count[HIT];
	}
    }
};

ostream& operator<<(ostream & out, const VM& vm) {
	out << "\n==Summary==\n\tHit: " << dec << vm.get_hit_count()
		<<  " Miss: " << vm.get_miss_count() 
		<< " VPNs:" << vm.get_vpns() << std::endl;
	return out;
}

VM vm;
void multiply(uint32_t* m1, uint32_t* m2, uint32_t* res)
{
    int x, i, j;
    for (i = 0; i < MS; i++) {
        for (j = 0; j < MS; j++) {
            vm.access(res + i*MS +j);
            for (x = 0; x < MS; x++) {
		vm.access(m1 + i*MS + x);
		vm.access(m2 + x*MS + j);
                vm.access(res + i*MS +j);
                // res[i][j] += m1[i][x] * m2[x][j];
                vm.access(res + i*MS +j);
            }
        }
    }
}

int main()
{
    uint32_t* m1 = (uint32_t*) 0xFACE00A000000000LL;  // fake virtual address; don’t access it
    uint32_t* m2 = (uint32_t*) 0xFACE00B000000000LL;  // fake virtual address; don’t access it
    uint32_t* res =  (uint32_t*) 0xFACE00C000000000LL; // fake virtual address; don’t access it
    multiply(m1, m2, res);
    cout << vm << endl;
    return 0;
}

