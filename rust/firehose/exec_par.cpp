//  g++ -std=c++17 exec_par.cpp 

#include <algorithm>
#include <chrono>
#include <random>
#include <vector>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <execution>
#include <thread>
#include <memory>

using namespace std;

void test() {
   shared_ptr<pair<shared_mutex, string>> my_pair =
       make_shared<pair<shared_mutex, string>>();
   vector<thread> thread_handles;
   for (int i = 0; i < 10; i++) {
     thread thread_handle([=] {
       shared_lock<shared_mutex> guard(my_pair->first);
       my_pair->second += "some characters";
     });
     thread_handles.push_back(move(thread_handle));
   }
   for (auto &thread_handle : thread_handles) {
     thread_handle.join();
   }
}

int main() {
   vector<int> v(10, 0);
   iota(begin(v), end(v), 0);
   int sum = 0;
   mutex sum_lock;
   for_each(execution::par, v.begin(), v.end(), [&](int &x) {
     x += 1;
     lock_guard<mutex> guard(sum_lock);
     sum += x;
   });
   cout << sum << endl;
   for(auto x: v) cout << x << " ";
   cout << endl;

   test();
   return 0;
}
