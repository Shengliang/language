/*
 * =============================================================================
 *
 *       Filename:  atomic_ex.cpp
 *
 *    Description:  atomic example
 *
 *        Version:  1.0
 *        Created:  02/12/2017 14:49:08
 *       Revision:  none
 *       Compiler:  gcc -g
 *
 *         Author:  Sheng-Liang Song (ssl), sheng-liang.song@sjsu.edu
 *   Organization:  SJSU
 *   http://www.cplusplus.com/reference/thread/thread/
 * =============================================================================
 */

#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

using namespace std;
atomic<int> acnt;
int cnt;
 
void f(void)
{
    for(int n = 0; n < 1000; ++n) {
        atomic_fetch_add_explicit(&acnt, 1, memory_order_relaxed); // atomic
        ++cnt; // undefined behavior, in practice some updates missed
    }
}
 
int main(void)
{
    thread t1(f);
    thread t2(f);
    t1.join();
    t2.join();
    cout << "The atomic counter is " << acnt.load() << endl;
    cout << "The non-atomic counter is " << cnt << endl;
    return 0;
}
