// g++ -std=c++11 pq.cpp 

#include <functional>
#include <queue>
#include <vector>
#include <iostream>
#include <tuple>
using namespace std;
typedef tuple<int, int> P;

ostream& operator<<(ostream& out, const P& p) {
   int a,b;
   tie(a,b) = p;
   return out << "(" << a << " " << b << ") ";
}

bool fless(const P& p1, const P& p2) {
   int a,b;
   int x,y;
   tie(a,b) = p1;
   tie(x,y) = p2;
#if 0
   if (a < x) 
     cout << p1 << " < " << p2 << endl;
   else 
     cout << p1 << " >= " << p2 << endl;
#endif
   return  (b < x);
}

int main(void) {
  vector<P> v;

  int s = 0;
  for (int i=1; i < 10; i++) {
     v.push_back(make_tuple(s, s+i));
     s+=(2*i);
  }
  for (const auto & e : v) {
     int a,b;
     tie(a,b) = e;
     cout << a << " " << b << endl;
  }

  for (int i=5; i <= 17; i++) {
    std::vector<P>::iterator low;
    low = std::lower_bound(begin(v), end(v), make_tuple(i,i), fless);
    int a,b;
    tie(a,b) = *low;
    if (i >= a) cout << i << " in " << *low << endl;
    else cout << i << " not in " << *low << endl;
  }
  return 0;
}
