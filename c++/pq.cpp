// g++ -std=c++11 pq.cpp

#include <functional>
#include <queue>
#include <vector>
#include <iostream>
#include <tuple>
using namespace std;
typedef tuple<int, int> P;

template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
        int x,y;
        tie(x,y) = q.top();
        cout << x << " " << y << endl;
        q.pop();
    }
    cout << '\n';
}
 
int main() {
    priority_queue<P, vector<P>, less<P> > q;
 
    for(int n : {1,8,5,6,3,4,0,9,7,2})
        q.push(make_tuple(n,128-n));
 
    print_queue(q);
 
    priority_queue<P, vector<P>, greater<P> > q2;
 
    for(int n : {1,8,5,6,3,4,0,9,7,2})
        q2.push(make_tuple(n, 128-n));
 
    print_queue(q2);
 
   {
   cout << "ly < ry " << endl;
    // Using lambda to compare elements.
    auto cmp = [](const P& left, const P& right) { 
      int lx,ly;
      int rx,ry;
      tie(lx,ly) = left;
      tie(rx,ry) = right;
      return ly < ry;
    };
    priority_queue<P, vector<P>, decltype(cmp)> q3(cmp);
 
    for(int n : {1,8,5,6,3,4,0,9,7,2})
        q3.push(make_tuple(n, 128-n));
    print_queue(q3);
   }
   {
   cout << "ly > ry " << endl;
    // Using lambda to compare elements.
    auto cmp = [](const P& left, const P& right) { 
      int lx,ly;
      int rx,ry;
      tie(lx,ly) = left;
      tie(rx,ry) = right;
      return ly > ry;
    };
    priority_queue<P, vector<P>, decltype(cmp)> q3(cmp);
 
    for(int n : {1,8,5,6,3,4,0,9,7,2})
        q3.push(make_tuple(n, 128-n));
    print_queue(q3);
   }
}

