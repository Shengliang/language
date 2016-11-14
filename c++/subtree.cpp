#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

bool adj[201][201];

#define dout if(1)cout

void foo(void) {
    int n;
    cin >> n;
    int w[n];
    int s= 0;
    dout << n << endl;
    for(int i=0; i<n; i++) {
        cin >> w[i];
        s+=w[i];
        dout << w[i] << " ";
    }
    dout << endl;
    int asz=s+1;
    int a[asz];
    for(int i=0; i<asz; i++) {
        cin >> a[i];
        dout << a[i] << " ";
    }
    dout << endl;
    for (int i=0; i<(n-1); i++) {
        int u,v;
        cin >> u >> v;
        adj[u][v] = 1;
        dout << u << " " << v <<  endl;
    }
    
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int q;
    cin >>  q;
    for(int i=0; i< q; i++) {
        foo();
    }
    return 0;
}

