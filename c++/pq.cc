#include <bits/stdc++.h>

using namespace std;

/* Option 1: use function pointer */
typedef bool (*mycmp_func)(pair<int, string>& a, pair<int, string>& b);
bool mycmp(pair<int, string>& a, pair<int, string>& b) {
  return (a.first == b.first) ? a.second > b.second : a.first > b.first;
};
typedef priority_queue<pair<int, string>, vector<pair<int, string>>, mycmp_func> pq_type;

/* Option 2: use operator< */
class Node {
public:
   int m_time;
   string m_s;
   Node(int time, string& s) : m_time(time), m_s(s) {}
   Node(int time, string s) : m_time(time), m_s(s) {}
   bool operator<(const Node& other) const {
      //return m_time < other.m_time;
      return (m_time == other.m_time) ? m_s > other.m_s : m_time > other.m_time;
   }
};
  
/* Option 3: use comparision class with operator() */
class mycomparison
{
  bool reverse;
public:
  mycomparison(const bool revparam=false) {
     reverse=revparam;
  }

  bool operator() (const int& lhs, const int&rhs) const {
    if (reverse)
       return (lhs>rhs);
    else
       return (lhs<rhs);
  }
};

typedef std::priority_queue<int,std::vector<int>,mycomparison> mypq_type;

int main(void)
{
   pq_type pq1(mycmp);
   pair<int, string> x1 = {3, "a"};
   pair<int, string> x2 = {3, "abbc"};
   pair<int, string> x3 = {3, "abc"};
   pq1.push(x1);
   pq1.push(x2);
   pq1.push(x3);

   while(!pq1.empty()) {
      auto& e = pq1.top();
      cout << pq1.size() << " " << e.first  << " " << e.second << endl;
      pq1.pop();
   }

   priority_queue<Node>  pq2;
   pq2.push({3, "a"});
   pq2.push({3, "abbc"});
   pq2.push({3, "abc"});

   while(!pq2.empty()) {
      auto & e = pq2.top(); 
      cout << pq2.size() << " " << e.m_time  << " " << e.m_s << endl;
      pq2.pop();
   }

   mypq_type pq3(mycomparison(true));
   pq3.push(30);
   pq3.push(5);
   pq3.push(30);
   while(!pq3.empty()) {
     cout << pq3.size() << " " << pq3.top() << " " << endl;
     pq3.pop();
   }

   mypq_type pq4(mycomparison(false));
   pq4.push(30);
   pq4.push(5);
   pq4.push(30);
   while(!pq4.empty()) {
     cout << pq4.size() << " " << pq4.top() << " " << endl;
     pq4.pop();
   }
   return 0;
}
