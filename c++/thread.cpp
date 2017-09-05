
/*
 * g++ -std=c++11 -pthread thread.cpp
 */

#include <iostream>
#include <thread>
// #include <chrono>
std::mutex g_mutex;

int init(int i) {
    std::cout << i << std::endl;
    return i+113;
}

const int a = init(7);
const int b = a >> 1;
int c = b;

void foo()
{
    // simulate expensive operation
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
    std::lock_guard<std::mutex> guard(g_mutex);
    std::cout << "foo:" << ++c << std::endl;
    }
}

void bar()
{
    // simulate expensive operation
    std::this_thread::sleep_for(std::chrono::seconds(1));
    {
    std::lock_guard<std::mutex> guard(g_mutex);
    std::cout << "bar:" << ++c << std::endl;
    }
}

int main()
{
    std::cout << a << " " << b << " " << b << std::endl;
    std::cout << "starting first helper...\n";
    std::thread helper1(foo);

    std::cout << "starting second helper...\n";
    std::thread helper2(bar);

    std::cout << "waiting for helpers to finish..." << std::endl;
    helper1.join();
    helper2.join();
 
    std::cout << "done!\n";
}
