#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int m[3][3];
bool f[3][3];   

void p() {
   for(int i=0; i<3; i++) {
     for(int j=0; j<3; j++) {
       cout << m[i][j] << " ";
     }
     cout << endl;
   }
   cout << endl;
}

int foo(int r, int c, int dr, int dc, int kr, int kc) {
    
    int cnt=0;
    cout << r << " " << c << " " << dr << " " << dc << " " << kr << " " << kc << endl;
    for(int i=0; i<3; i++) {
        for(int j=0;  j<3; j++) {
            f[i][j]=false;
        }
    }
    
    for(int i=0; i<9; i++) {
        f[r][c]=true;
        if (m[r][c] != (i+1)) {
            cnt+=abs(m[r][c] -(i+1));
        }
        cout << m[r][c] << " " <<  (i+1) << endl;
        int nr=r,nc=c;
        nr=r+dr+3; nr%=3;
        nc=c+dc+3; nc%=3;
        if (f[nr][nc]==true) {
            nr = r+kr+3;
            nr%=3;
            nc = c+kc+3;
            nc%=3;
        }
        r=nr;
        c=nc;
    }
    
    cout << endl;
   p();
    return cnt;
}
   
int k() {
    int c21 = foo(2, 1,  1,  1, -1,  0);
    int c01 = foo(0, 1, -1, -1,  1,  0);
    int t1 = min(c21, c01);
    int c10 = foo(1, 0,  1, -1,  0,  1);
    int c12 = foo(1, 2, -1,  1,  0, -1);
    int t2 = min(c10, c12);
    int t= min(t1, t2);
    return t;
}

int g() {
    int c21 = foo(2, 1,  1, -1, -1,  0);
    int c01 = foo(0, 1, -1,  1,  1,  0);
    int t1 = min(c21, c01);
    int c10 = foo(1, 0, -1, -1, 0,  1);
    int c12 = foo(1, 2,  1,  1, 0, -1);
    int t2 = min(c10, c12);
    int t= min(t1, t2);
    return t;
}

        
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
 
    for(int i=0; i<9; i++) {
        cin >> m[i/3][i%3];
    }
   p();
    int k1=k();
    int k2=g();
    cout << min(k1, k2) << endl;
    return 0;
}

