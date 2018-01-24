/*
 * Reference:
 * CppCon 2017: Louis Brandy “Curiously Recurring C++ Bugs at Facebook”
 * https://www.youtube.com/watch?v=lkgszkPnV8g
 * http://en.cppreference.com/w/cpp/thread/scoped_lock
 */
#include <iostream>
#include <iterator>
#include <algorithm>
#include <thread>
#include <mutex>
#include <boost/bind/placeholders.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/function.hpp>
#include <boost/thread.hpp>
 
typedef boost::mutex mutex_t;
typedef boost::mutex::scoped_lock scoped_lock_t;

class AInt {
   int m_i;
   mutex_t m_mutex;
public:
   AInt() : m_i(0), m_mutex() { }

   void bug1_inc() {
      scoped_lock_t(this->m_mutex);
      ++m_i;
   }
   void bug2_inc() {
      scoped_lock_t(m_mutex);
      ++m_i;
   }
   void ok_inc() {
      scoped_lock_t lock(m_mutex);
      ++m_i;
      std::cout << std::this_thread::get_id() << ": " << m_i << '\n';
   }
   AInt& operator++() {
      bug1_inc();
      bug2_inc();
      ok_inc();
      return *this;
   }
   AInt& operator--() {
	scoped_lock_t lock(this->m_mutex);
	--m_i;
	return *this;
   }
   int get() const { return m_i; }
   // friend std::ostream& operator<<(std::ostream& out, const AInt& a);
};

std::ostream& operator<<(std::ostream& out, const AInt& a) {
	return out << a.get();
}

AInt g_x;
void thread_main()
{
    ++g_x;
}
 
int main(void)
{
    std::cout << __func__ << ": " << g_x << '\n';
    std::thread t1(thread_main);
    std::thread t2(thread_main);
    t1.join();
    t2.join();
    std::cout << __func__ << ": " << g_x << '\n';
    return 0;
}

