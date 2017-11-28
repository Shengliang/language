// References:
// A simple and effective algorithm for virtual memory
// infolab.stanford.edu/~manku/quals/zpapers/81-wsclock.pdf.gz
// g++ -std=c++11  vm_clock.cpp  

#include<algorithm>
#include<atomic>
#include<map>
#include<queue>
#include<string>
#include<vector>
#include<iostream>

#include <unistd.h> // pid_t getpid(void);

using namespace std;
#define HIT  0
#define MISS 1

class VM
{
    std::vector<uint64_t> m_clock;
    std::vector<char> m_use_bit;
    std::vector<char> m_dirty_bit;
    std::atomic<uint32_t> m_hand;
    uint32_t m_page_offset;
    uint32_t m_size;
    std::queue<uint64_t> m_clean_request_que;
    uint64_t m_count[2];
    std::map<uint64_t, uint32_t> m_vpns;
public:
    uint64_t get_hit_count() const { return m_count[HIT];}
    uint64_t get_miss_count() const { return m_count[MISS];}
    /* 16KB Page (14-bit page offset)
     * 16GB Page Buffer Memory (1M Pages)
     */
    VM(uint32_t size = 1024*1024, uint32_t page_offset = 14)
	: m_size(size), m_page_offset(page_offset) {
	m_clock.resize(size, 0LL);
	m_use_bit.resize(size, 0);
	m_dirty_bit.resize(size, 0);
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
		if (old_use_bit)
			continue;

		if (m_dirty_bit[m_hand]) {
			// schedule page for cleaning
			m_clean_request_que.push(m_hand);
			continue;
		}

		// replace page
		uint64_t old_vpn = m_clock[m_hand];
		m_vpns.erase(old_vpn);
		m_vpns[vpn] = m_hand;
		m_clock[m_hand] = vpn;
		break;
	}
    }

    void access(void* ptr) {
	uint64_t vpn = ((uint64_t) ptr) >> m_page_offset;
	pid_t pid = getpid();
	const auto & search = m_vpns.find(vpn);
	if (search == m_vpns.end()) {
    		replace(vpn);
		++m_count[MISS];
	} else {
		m_use_bit[search->second] = 1;
		++m_count[HIT];
	}
	
    }
};

ostream& operator<<(ostream & out, const VM& vm) {
	out << "\n==Summary==\n\tHit: " << vm.get_hit_count()
		<<  " Miss: " << vm.get_miss_count() << std::endl;
	return out;
}
VM vm;
#define MS 16
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
