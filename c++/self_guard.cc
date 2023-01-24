#include <iostream>
#include <memory>
#include <mutex>
using namespace std;
struct X {
  char data[1024];
  ~X() { cout << __PRETTY_FUNCTION__ << this << " " << endl; }
};
struct B {
  X x;
  virtual ~B() { cout << __PRETTY_FUNCTION__ << " " << this << endl; }
  /*Delete this(self) when the function is returned. */
  virtual void SelfGuardRunOnceTimeOnly() {
    std::unique_ptr<B> self_guard(this);
    cout << __PRETTY_FUNCTION__ << " BEGIN " << this << endl;
    Run();
    cout << __PRETTY_FUNCTION__ << " END Delete:" << this << endl;
  }
  virtual void Run() = 0;
};
struct C : public B {
  virtual ~C() { cout << __PRETTY_FUNCTION__ << " " << this << endl; }
  void Run() override { cout << __PRETTY_FUNCTION__ << " " << this << endl; }
};
int main() {
  (new C)->SelfGuardRunOnceTimeOnly();
  return 0;
}
