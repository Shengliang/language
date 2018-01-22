/*
 * Reference:
 * CppCon 2017: Louis Brandy “Curiously Recurring C++ Bugs at Facebook”
 * https://www.youtube.com/watch?v=lkgszkPnV8g
 * http://en.cppreference.com/w/cpp/thread/scoped_lock
 */
#include <boost/bind/placeholders.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>

#include <iostream>
#include <iterator>
#include <algorithm>
#include <thread>
#include <mutex>

typedef std::istream_iterator<int> in;
using namespace boost::lambda;
 
typedef boost::mutex my_mutex;
typedef boost::mutex::scoped_lock my_scoped_lock;


class AInt {
   int m_i;
   my_mutex m_mutex;
public:
   AInt() : m_i(0), m_mutex() { }
   int& operator++() {
      // my_scoped_lock(this->m_mutex); // BUG1 CODE
      // my_scoped_lock(m_mutex);       // BUG2 CODE
      my_scoped_lock lock(m_mutex);     // YES!
      ++m_i;
      return m_i;
   }
   int& operator--() {  my_scoped_lock lock(this->m_mutex); --m_i; return m_i;}
   int get() const { return m_i; }
   // friend std::ostream& operator<<(std::ostream& out, const AInt& a);
};

std::ostream& operator<<(std::ostream& out, const AInt& a) {
	return out << a.get();
}

int g_i = 0;
my_mutex g_i_mutex;  // protects g_i

AInt g_x;
 
void safe_increment()
{
    ++g_x;

    // my_scoped_lock(g_i_mutex); // BUG CODE
    my_scoped_lock lock(g_i_mutex); // FIXED
    ++g_i;
 
    std::cout << std::this_thread::get_id() << ": " << g_i << " " << g_x << '\n';
 
    // g_i_mutex is automatically released when lock
    // goes out of scope
}
 
int test1(void)
{
    std::cout << __func__ << ": " << g_i << '\n';
    std::thread t1(safe_increment);
    std::thread t2(safe_increment);
    t1.join();
    t2.join();
    std::cout << __func__ << ": " << g_i << '\n';
    return 0;
}

int test2(void)
{
    std::for_each(in(std::cin), in(),
	std::cout << (::boost::lambda::_1 * 3) << " " );
    return 0;
}

int main(void)
{
    std::cout << "Type 1 2[enter]:";
    int t = 0;
    std::cin >> t;
    switch (t) {
      case 1: test1(); break;
      case 2: test2(); break;
      default: break;
    }
    return 0;
}

