
#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#include <mutex>

std::map<std::string, std::string> g_pages;
std::mutex g_pages_mutex;

int cnt = 0;
class A {
 public:
   A() { std::cout << "A()" << std::endl; }
   ~A() { std::cout << "~A()" << std::endl; }
};
class B {
  int x;
public:
  B(int v = 0) : x(v) { }

  //Prefix Increment Operator Function
 B operator++(void) {
	 ++x;
	 std::cout << x << std::endl;
	 return *this;
 }
  //Postfix Increment Operator Function
 B operator++(int) {
	 B tmp(x);
	 ++x;
	 return tmp;
 }

};

void save_page(const std::string &url)
{
    // simulate a long page fetch
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::string result = "fake content ";
    B b;
    for(int i = 0; i < 10; ++i, ++b) {
       A a;
       {
        std::lock_guard<std::mutex> guard(g_pages_mutex);
        g_pages[url + std::to_string(cnt)] = result + std::to_string(cnt);
        cnt++;
       }
       std::this_thread::sleep_for(std::chrono::microseconds(2));
    }
}
int main()
{
    std::thread t1(save_page, "http://foo");
    std::thread t2(save_page, "http://bar");
    t1.join();
    t2.join();
 
    // safe to access g_pages without lock now, as the threads are joined
    for (const auto &pair : g_pages) {
        std::cout << pair.first << " => " << pair.second << '\n';
    }
}
