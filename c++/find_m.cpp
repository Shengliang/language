#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

#define N 1000002
int ar[N];

inline void qswap(int& a, int &b){
  int t = b;
  b=a;
  a=t;
}

inline int partition(int i, int j) {
   int pl=0;
   int f =0;
   int x = ar[j];
   for(int t=i; t<j; t++) {
       if (ar[t] > x) {
           if (f==0) {
               f=1;
               pl=t;
           }
       } else if(f==1) {
           qswap(ar[t], ar[pl]);
           pl++;
       }
   }
   if ((f==1) && (pl<j) && (pl>=i))  {
      qswap(ar[pl], ar[j]);
   }
   return pl;
}

                      


// Find median: find the Pivot reached the N/2 th element.

int main(void) {
    int n;
    cin >> n;
    for(int i=0; i<n; i++) {
        int t;
        cin >> t;
        ar[i] = t;
    }
    
    int i = 0;
    int j = n - 1;
    int p=0, half = (n >> 1);
    for(;;) {  
        p = partition(i, j);
        if (p==half) {
            break;
        }
        else if (p > half) {
           j=p-1;
        } else {
           i=p+1;
       }
    } 
    cout << ar[p] << endl;
    return 0;
}


