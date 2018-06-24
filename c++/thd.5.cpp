// thread example
#include <iostream>       // std::cout
#include <thread>         // std::thread
#include <chrono>         // std::chrono::seconds


#include <unistd.h>
#include <cstdlib>
#include <ctime>
 
using namespace std;
// #define USE_ATOMIC

#ifdef USE_AOTMIC
atomic<int> x(0);
#else
volatile int x = 0;
#endif

atomic<int> readx(0);
atomic<int> got1(0);
atomic<int> other_done(0);

long long countArr[5] = {0};
int M[5][5];


void thread_main(int id)
{
   /*  initialize random seed: */
   std::thread::id this_id = std::this_thread::get_id();
   srand (time(NULL));
   auto start = std::chrono::high_resolution_clock::now();
   for(int i=0; i<5; i++) {
#if 1
	   // slow down thread 0, 4th loop.
	   // make sure thread 1 write 1 completes.
	   if (id ==0 && i==4) { 
    		std::this_thread::sleep_for (std::chrono::seconds(1));
	   }

	   int t = x;
	   // in 1st loop, make sure everyone read the initial value,0.
	   if (i==0) {
  	        ++readx;
	   }

	   // if thread 0, read 1 in 4th loop; set got1 flag.  
	   if (id ==0 && i==4) {
		  while (t != 1) t = x;
		  got1 = 1;
	   }
	   t = t + 1;

	   // thread 0: wait other threads done its increments.
	   if (id ==0 && i==4) { 
		   while(other_done!=4);
	   }

	   // make sure threads read x's initial value 0.
	   while (readx!=5);

	   // block other threads until thread 0 got 1.
	   if (id!=0 && i>0)
	     while (got1==0);

	   x = t;

	   M[id][i] = x;

	   // counts other thread done loops
	   if (i==4 && id!=0)
		   ++other_done;

#else
	   ++x;
#endif
   }
   auto end = std::chrono::high_resolution_clock::now();
   std::chrono::duration<double, std::milli> elapsed = end-start;
   countArr[id] = elapsed.count();
}

int main() 
{
 
  thread s0(thread_main, 0);
  thread s1(thread_main, 1);
  thread s2(thread_main, 2);
  thread s3(thread_main, 3);
  thread s4(thread_main, 4);

  s0.join();
  s1.join();
  s2.join();
  s3.join();
  s4.join();

  for (int i = 0; i < 5; i++) {
     std::cout << "Thread:" << i << " waited " << countArr[i] << " ms: ";
     for(int j=0; j< 5; j++) {
	     std::cout << M[i][j] << " ";
     }
     std::cout << std::endl; 
  }
  std::cout << x << std::endl;
  return 0;
}
