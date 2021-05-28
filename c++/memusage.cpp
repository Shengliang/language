#include <unistd.h>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <vector>
#include <iomanip>

#include <chrono>

#include <iostream>
#include <thread>

   using std::ios_base;
   using std::ifstream;
   using std::string;


   using std::chrono::high_resolution_clock;
   using std::chrono::duration_cast;
   using std::chrono::duration;
   using std::chrono::milliseconds;
   using std::cout;
   using std::endl;


// Reference
//  https://stackoverflow.com/questions/22387586/measuring-execution-time-of-a-function-in-c
//  https://stackoverflow.com/questions/669438/how-to-get-memory-usage-at-runtime-using-c
//  https://chromium.googlesource.com/chromium/src/+/refs/heads/main/base/containers/README.md
//
// bash   for i in {1..9} ; do  ./a.out $i 10000000; done
/*
Test size:10000000 16ms 16.6061 ms VM:1.07422 MB RSS:2676 uint64_t arr[]
Test size:10000000 139ms 139.19 ms VM:1.19531 MB RSS:2676 vector<bool>
Test size:10000000 21ms 21.9735 ms VM:9.53906 MB RSS:11052 vector<char>
Test size:10000000 41ms 41.2841 ms VM:38.1484 MB RSS:40360 vecotr<int>
Test size:10000000 2223ms 2223.03 ms VM:422.223 MB RSS:433804 unordered_set<int>
Test size:10000000 2442ms 2442.52 ms VM:422.223 MB RSS:433760 unordered_map<int,int>
Test size:10000000 8036ms 8036.71 ms VM:457.746 MB RSS:470152 set<int>
Test size:10000000 8234ms 8234.63 ms VM:457.746 MB RSS:470200 map<int,int>
*/

void long_operation()
{
    /* Simulating a long, heavy operation. */
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(150ms);
}

//////////////////////////////////////////////////////////////////////////////
//
// process_mem_usage(double &, double &) - takes two doubles by reference,
// attempts to read the system-dependent data for a process' virtual memory
// size and resident set size, and return the results in MB.
//
// On failure, returns 0.0, 0.0

void process_mem_usage(double& vm_usage, double& resident_set)
{
   vm_usage     = 0.0;
   resident_set = 0.0;

   // 'file' stat seems to give the most reliable results
   //
   ifstream stat_stream("/proc/self/stat",ios_base::in);


   // dummy vars for leading entries in stat that we don't care about
   //
   string pid, comm, state, ppid, pgrp, session, tty_nr;
   string tpgid, flags, minflt, cminflt, majflt, cmajflt;
   string utime, stime, cutime, cstime, priority, nice;
   string O, itrealvalue, starttime;

   // the two fields we want
   //
   unsigned long vsize;
   long rss;

   stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr
               >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt
               >> utime >> stime >> cutime >> cstime >> priority >> nice
               >> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest

   stat_stream.close();

   long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
   vm_usage     = vsize / (1024*1024.0);
   resident_set = rss * page_size_kb;
}

void print_stats(std::chrono::time_point<std::chrono::high_resolution_clock> t1, double vm1, double rss1, string name) {
   double vm2, rss2;
   auto t2 = high_resolution_clock::now();
   process_mem_usage(vm2, rss2);
   /* Getting number of milliseconds as an integer. */
   auto ms_int = duration_cast<milliseconds>(t2 - t1);
   /* Getting number of milliseconds as a double. */
   duration<double, std::milli> ms_double = t2 - t1;
   cout << ms_int.count() << "ms " << ms_double.count() << " ms VM:" << vm2-vm1 << " MB RSS:" << rss2-rss1 << " " << name << endl;
   //std::setprecision(3)  
}

int main(int argc, char*argv[])
{
   int size = 1000000;
   int op = 1;
   if (argc >= 2) {
     op = argv[1][0] - '0';
   }
   if (argc > 2) {
     size = atoi(argv[2]);
   }
   double vm, rss;
   cout <<  "Test size:" << size << " ";
   switch (op) {
   case 1: {
      process_mem_usage(vm, rss);
      auto t1 = high_resolution_clock::now();
      uint64_t arr[size/64];
      for(int i = 0; i < size; ++i) arr[i/64] = i%64;
      print_stats(t1, vm, rss, "uint64_t arr[]");
   } break;
   case 2:{
      process_mem_usage(vm, rss);
      auto t1 = high_resolution_clock::now();
      std::vector<bool> ss(size,0);
      for(int i = 0; i < size; ++i) ss[i] = true;
      print_stats(t1, vm, rss, "vector<bool>");
   } break;
   case 3:{
      process_mem_usage(vm, rss);
      auto t1 = high_resolution_clock::now();
      std::vector<char> ss(size,0);
      for(int i = 0; i < size; ++i) ss[i] = i&0xFF;
      print_stats(t1, vm, rss, "vector<char>");
   } break;
   case 4:{
      process_mem_usage(vm, rss);
      auto t1 = high_resolution_clock::now();
      std::vector<int> ss(size,0);
      for(int i = 0; i < size; ++i) ss[i] = i;
      print_stats(t1, vm, rss, "vecotr<int>");
   } break;
   case 5:{
      process_mem_usage(vm, rss);
      auto t1 = high_resolution_clock::now();
      std::unordered_set<int> ss;
      for(int i = 0; i < size; ++i) ss.insert(i);
      print_stats(t1, vm, rss, "unordered_set<int>");
   } break;
   case 6:{
      process_mem_usage(vm, rss);
      auto t1 = high_resolution_clock::now();
      std::unordered_map<int,int> ss;
      for(int i = 0; i < size; ++i) ss[i] = i;
      print_stats(t1, vm, rss, "unordered_map<int,int>");
   } break;
   case 7:{
      process_mem_usage(vm, rss);
      auto t1 = high_resolution_clock::now();
      std::set<int> ss;
      for(int i = 0; i < size; ++i) ss.insert(i);
      print_stats(t1, vm, rss, "set<int>");
   } break;
   case 8:{
      process_mem_usage(vm, rss);
      auto t1 = high_resolution_clock::now();
      std::map<int,int> ss;
      for(int i = 0; i < size; ++i) ss[i] = i;
      print_stats(t1, vm, rss, "map<int,int>");
   } break;
      default: break;
   }
}
