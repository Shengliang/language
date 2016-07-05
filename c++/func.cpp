/* g++ -std=c++11 func.cpp */
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

class Test {
  private:
  std::function<int(const Test & test)> _monitor_func;
  int _x;
  int _y;
 public:
     Test(int x=0, int y=0):_x(x), _y(y), _monitor_func(nullptr)  { }
     int run(void) {
       int rc = 0;
       if(_monitor_func) rc  = _monitor_func(*this);
       return rc;
     }
     void register_monitor(std::function<int(const Test & test)> monitor_func) {
           _monitor_func = monitor_func;
     }
     int getValue(void) const {
       return _x+_y;
     }
  protected:
};

int main()
{
    int rc;
    std::vector<int> c = {1, 2, 3, 4, 5, 6, 7};
    int x = 5;
    c.erase(std::remove_if(c.begin(), c.end(), [x](int n) { return n < x; }), c.end());

    std::cout << "c: ";
    std::for_each(c.begin(), c.end(), [](int i){ std::cout << i << ' '; });
    std::cout << '\n';

    // the type of a closure cannot be named, but can be inferred with auto
    auto func1 = [](int i) { return i + 4; };
    std::cout << "func1: " << func1(6) << '\n';

    // like all callable objects, closures can be captured in std::function
    // (this may incur unnecessary overhead)
    std::function<int(int)> func2 = [](int i) { return i + 4; };
    std::cout << "func2: " << func2(6) << '\n';

    Test test(1,2);
    std::function<int(const Test & test)> monitor_func = [](const Test & test) -> int {
      int v = test.getValue(); cout << v  << " " << endl; return v;
    };
    test.register_monitor(monitor_func);
    rc = test.run();
    cout << "rc: " << rc << endl;
}

