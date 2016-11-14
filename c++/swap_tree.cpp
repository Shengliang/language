#include <stdlib.h>
#include <string.h>

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
#define dout if(0)cout
int L[1025];
int R[1025];
int D[1025];
/*
11
1 2 3
2 4 -1
3 5 -1
4 6 -1
5 7 8
6 -1 9
7 -1 -1
8 10 11
9 -1 -1
10 -1 -1
11 -1 -1

2
2
4
*/
int fdepth(int x) {
  if (x==-1)
     return -1;
  int l = L[x];
  int r = R[x];
  int dl=fdepth(l);
  int dr=fdepth(r);
  return 1+max(dl,dr);  
}

void set_depth(int x, int md) {
  if (x==-1)
    return;
  int l = L[x];
  int r = R[x];
  set_depth(l, md+1);
  D[x] = md;
  dout << x << "--> " << md << endl;
  set_depth(r, md+1);
  return;
}


bool is_swap(int x, const map<int, bool>&m) {
  int d = D[x];
  return (m.find(d) != end(m));
}

void inorder(int x, const map<int, bool>& m) {
  if (x==-1)
    return ;
  int l = L[x];
  int r = R[x];
  if (l==-1 && r==-1) {
    cout << x << " ";
    return;
  } 
  bool s = is_swap(x, m);
  if(s) {
    int t = l;
    l = r;
    r = t;
    L[x] = l;
    R[x] = r;
    dout << "swap: " << x <<  " " << D[x] << endl;
  }
  inorder(l, m);
  cout << x << " ";
  inorder(r, m);
  return;
}

int main() {

    int n;
    cin >> n;
    memset(L, -1, sizeof(L));
    memset(R, -1, sizeof(R));
    memset(D, -1, sizeof(D));
    L[0] = R[0] = 1;
    for(int i=1; i<= n; i++) {
       cin >> L[i] >> R[i];
       dout << i << " " << L[i] << " " << R[i] <<endl;
    }     
    int lmax = fdepth(0);
    dout << "depth:" << lmax << endl; 
    set_depth(0, 0);
    int T;
    cin >> T;
    for(int i=0; i<T; i++) {
       int k; 
       cin >> k;
       map<int, bool> m;
       for(int l=1; (l*k) <= lmax; l++) {
          m[l*k]=true; 
          dout << "level:" << l*k << endl;
       }
       inorder(1, m);
       cout << endl;
    }
    return 0;
}

