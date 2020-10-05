
#include<bits/stdc++.h>

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
  int len;
  char *data;
  request_t(int _id, int _len, const char* _data) {
	  id = _id;
	  len = _len;
	  data = new char[len];
	  memcpy(data, _data, len);
	  std::cout << __FUNCTION__ << " " << id <<  std::endl;
  }
  ~request_t(void) {
	  std::cout << __FUNCTION__ << " " << id << std::endl;
	  if(data) {
		  delete [] data;
		  data = nullptr;
	  }
  }
};

class request_hdl_t {
	std::queue<std::unique_ptr<request_t>> q;
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
		std::string data = "hello";
		request_hdl->push(std::make_unique<request_t>(i, data.length(), data.c_str()));
	}
	while(!request_hdl->empty()) {
	    auto e = request_hdl->pop();
	    std::cout << e->id << " " << e->len << " " << e->data << std::endl;
	}

    // Use the default constructor.
    std::unique_ptr<Vec3> v1 = std::make_unique<Vec3>();
    // Use the constructor that matches these arguments
    std::unique_ptr<Vec3> v2 = std::make_unique<Vec3>(0, 1, 2);
    // Create a unique_ptr to an array of 5 elements
    std::unique_ptr<Vec3[]> v3 = std::make_unique<Vec3[]>(5);

    std::cout << "make_unique<Vec3>():      " << *v1 << '\n'
              << "make_unique<Vec3>(0,1,2): " << *v2 << '\n'
              << "make_unique<Vec3[]>(5):   " << '\n';
    for (int i = 0; i < 5; i++) {
        std::cout << "     " << v3[i] << '\n';
    }

{
    std::unique_ptr<int>  myptr;
    myptr = std::make_unique<int>();
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
