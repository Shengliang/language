
// g++ --std=c++14 make_unique.cpp
// g++ -g  --std=c++17 make_unique.cpp  for mp.insert_or_assign(id, std::move(p));
#include<bits/stdc++.h>


namespace c11 {
// g++ --std=c++11 make_unique.cpp
//  does not support  std::unique_ptr<Vec3[]> v3 = std::make_unique<Vec3[]>(5);
template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
};

#define my_make_unique std::make_unique

struct my_deleter {
  template <class T>
  void operator()(T* p) {
    std::cout << __FUNCTION__ << std::endl;
    delete p;
  }
};


class state_deleter {  // a deleter class with state
  int count_;
public:
  state_deleter() : count_(0) {}
  template <class T>
  void operator()(T* p) {
    std::cout << "[deleted #" << ++count_ << "]\n";
    delete p;
  }
};


struct Vec3
{
    int x, y, z;
    Vec3() : x(0), y(0), z(0) { }
    Vec3(int x, int y, int z) :x(x), y(y), z(z) { }
    friend std::ostream& operator<<(std::ostream& os, Vec3& v) {
        return os << '{' << "x:" << v.x << " y:" << v.y << " z:" << v.z  << '}';
    }
};

struct request_t {
  int id;
  std::vector<char>  data;
  request_t(int _id, const std::vector<char>& _data) : id(_id), data(_data) {
	  std::cout << __FUNCTION__ << " " << id <<  std::endl;
  }
  ~request_t(void) {
	  std::cout << __FUNCTION__ << " " << id << std::endl;
  }
};

class request_hdl_t {
	std::queue<std::unique_ptr<request_t>> q;
	std::unordered_map<int, std::unique_ptr<request_t>> mp;
	public:
	request_hdl_t() { }
	void push(std::unique_ptr<request_t> p) {
		q.push(std::move(p));
	}
	std::unique_ptr<request_t> pop(void) {
		auto rc = std::move(q.front());
		q.pop();
		return std::move(rc);
	}
	void insert(int id, std::unique_ptr<request_t> p) {
		// c++17 mp.insert_or_assign(id, std::move(p));
		std::vector<char> data = {'t','e','s','t'};
		mp[id] = std::move(p);
		id+=100;
		//mp[id] = my_make_unique<request_t>(id, data);
		mp[id].reset(new request_t(id, data));
		std::cout << id << std::endl;
	}
	void process(void) {
		for(auto & kv: mp) {
		     auto& e = kv.second;
	             std::cout << e->id << " " << e->data.size() << " ";
	             for(auto ch: e->data) std::cout << ch ; std::cout << std::endl;
		     // mp.erase(e->id); ==> crash!
		}
		std::cout << " use iterator " << std::endl;
		for(auto it = mp.begin(); it != mp.end(); ) {
		     auto& e = it->second;
	             std::cout << e->id << " " << e->data.size() << " ";
	             for(auto ch: e->data) std::cout << ch ; std::cout << std::endl;
		     it = mp.erase(it);
	        }
	}
	int size() {
		return q.size();
	}
	bool empty() {
		return q.empty();
	}
};

std::unique_ptr<request_hdl_t>  request_hdl;


int main(void)
{
	request_hdl.reset(new request_hdl_t());
	for(int i = 0; i < 8; ++i) {
		std::vector<char> data = {'h','e','l','l','o'};
		request_hdl->push(my_make_unique<request_t>(i, data));
	}
	while(!request_hdl->empty()) {
	    auto e = request_hdl->pop();
	    std::cout << e->id << " " << e->data.size() << " ";
	    for(auto ch: e->data) std::cout << ch ; std::cout << std::endl;
	    int id = e->id;
	    request_hdl->insert(id, std::move(e));
	}

	request_hdl->process();

    // Use the default constructor.
    std::unique_ptr<Vec3> v1 = my_make_unique<Vec3>();
    // Use the constructor that matches these arguments
    std::unique_ptr<Vec3> v2 = my_make_unique<Vec3>(0, 1, 2);
    // Create a unique_ptr to an array of 5 elements
    std::unique_ptr<Vec3[]> v3 = my_make_unique<Vec3[]>(5);

    std::cout << "make_unique<Vec3>():      " << *v1 << '\n'
              << "make_unique<Vec3>(0,1,2): " << *v2 << '\n'
              << "make_unique<Vec3[]>(5):   " << '\n';
    for (int i = 0; i < 5; i++) {
	    v3[i] = {i, i*i, i*i*i};
        std::cout << "     " << v3[i] << '\n';
    }

{
    std::unique_ptr<int>  myptr;
    myptr = my_make_unique<int>();
    std::cout << *myptr << std::endl;
    *myptr = 5;
    std::cout << *myptr << std::endl;
}

{
    std::cout << "use deleter" << std::endl;
    std::unique_ptr<int,my_deleter>  myptr;
    myptr.reset(new int(42));
    std::cout << *myptr << std::endl;
    *myptr = 5;
    std::cout << *myptr << std::endl;
}
    return 0;
}

