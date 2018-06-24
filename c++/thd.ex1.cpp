// g++ -std=c++11 -g thd.ex.cpp -o a.out
// g++ -DADD_SLEEP -std=c++11 -g thd.ex.cpp -o a.out.sleep 
// 
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <chrono>         // std::chrono::seconds

using namespace std;

// global shared variable x.
volatile int x = 0;

void thread_main(int id)
{
   for(int i=0; i<5; i++) {
	 int t = x;
#ifdef ADD_SLEEP
    	 std::this_thread::sleep_for (std::chrono::microseconds(1));
#endif
	 t = t + 1;
	 x = t;
   }
}

int main(void) 
{
  try {
  thread s0(thread_main, 0);
  thread s1(thread_main, 1);
  thread s2(thread_main, 2);
  thread s3(thread_main, 3);
  thread s4(thread_main, 4);

#ifdef IJOIN
  s0.join();
  s1.join();
  s2.join();
  s3.join();
  s4.join();
#endif

  std::cout << x << std::endl;
  } catch(...) {
  }

  return 0;
}
