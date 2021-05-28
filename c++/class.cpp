#include<iostream>
#include<string>
#include<memory>
#include<map>
#include<vector>
#include<algorithm>

using namespace std;

namespace Example {
class B {
public:
	inline B(int x = __LINE__ ) : v(x) { cout << __FILE__ << " " << __LINE__ << endl; }
	int v;
};

template <typename T>
inline T const& Max(T const & a, T const& b)
{
  return a < b ? b : a;
}

template <typename T>
inline bool comp(T const & a, T const& b)
{
  return a < b;
}


template <class KType, class VType>
class A {
private:
  vector<VType> values_;
  A(const map<KType, VType>& hmap) : hmap_(hmap) {
    for(auto e : hmap_) {
        keys_.push_back(e.first);
        values_.push_back(e.second);
    }
  }
protected:
  vector<KType> keys_;

public:
  map<KType, VType> hmap_;

  ~A() = default;
  A() = delete;
  A(const A&) = delete;
  A(const A&&) = delete;
  static shared_ptr<A<KType, VType>> Create(const map<KType, VType>& hmap) {
   return shared_ptr<A<KType, VType>>(new A<KType, VType>(hmap));
  }

  void print() {
    for(const auto& k : keys_) {
      cout << k << endl;
    }
    for(const auto& v : values_) {
      cout << v << endl;
    }
    cout << *std::max_element(values_.begin(), values_.end(), comp<VType>) << endl;
  }
};

} // namespace Example


using namespace Example;

int main(int argc, char* argv[]) {
	B a(__LINE__);
	B b(__LINE__);
	cout << a.v << " " << b.v << endl;
  map<string, int> persons;
  persons["Alice"] = 44;
  persons["Bob"] = 45;
  persons["David"] = 46;
  shared_ptr<A<string, int>> sp_A = A<string, int>::Create(persons);
  sp_A->print();
  return 0;
}
