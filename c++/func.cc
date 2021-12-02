
#include<bits/stdc++.h>

using namespace std;
class Q {
  mutable std::mutex m_queueMutex;
  std::condition_variable m_nonemptyCondition;
  const uint32_t m_popTimeoutMs = 10;
public:
  queue<int> m_queue;

  void push(int v) {
	  m_queue.push(v);
  }
  int pop() {
     int v = -1;
     chrono::milliseconds timeout(m_popTimeoutMs);
     unique_lock<std::mutex> lock(m_queueMutex);
     cout << "pop():m_queue address:" << &m_queue << endl;
     bool waitDone = m_nonemptyCondition.wait_for(
     lock, timeout, [=] { 
         // Note: = copy this pointer by value.  
	 //         We are not copy the object or member data by value.
         cout << "wait_for:m_queue address:" << &m_queue << endl;
         return !m_queue.empty(); 
     });
     if (!waitDone) {
       return v;
     }
     v = m_queue.front();
     m_queue.pop();
     return v;
  }
};



int main(void) {
  Q q;
  q.push(1);
  cout << q.pop() << endl;
  return 0;
}
