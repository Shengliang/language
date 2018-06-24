/*
 * http://www.boost.org/doc/libs/1_63_0/libs/smart_ptr/sp_techniques.html
 */
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <thread>
#include <mutex>
#include <memory>

template<class T> class pointer
{
private:

    T * p_;

public:

    explicit pointer(T * p): p_(p)
    {
    }

    std::shared_ptr<T> operator->() const
    {
        p_->prefix();
        return std::shared_ptr<T>(p_, std::mem_fun(&T::suffix));
    }
};

#define WHERE() std::cout << __FUNCTION__ << std::endl
class X
{
private:

    void prefix() { WHERE(); }
    void suffix() { WHERE(); }
    friend class pointer<X>;
    
public:
    X() { WHERE(); }
    ~X() { WHERE(); }
    void f() { WHERE(); }
    void g() { WHERE(); }
};

int main()
{
    X x;

    pointer<X> px(&x);

    x.f();
    px->f();
    px->g();
}

