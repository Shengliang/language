#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_N  200001
#define MAX_V 1000001
int a[MAX_N];
int v[MAX_V];
int ks[MAX_N];

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    cin >> n;
    int xe,yb;
    int k;
    int c;
    xe=0;
    yb=0;
    k=n-1;
    c=0;
    for(int i=0; i<n; i++) {
         ks[i] = -1;
    }
    for(int i=0; i<MAX_V; i++) v[i] = 0;
    for(int i=0; i<n; i++) {
        char op;
        cin >> op;

        if (op == '+') {
            cin >> a[c];
            v[ a[c] ]++;
            c++;
        } else {
            v[ a[c] ]--;
            c--;
        }

        if (c==0) {
            k=0;
            xe=-1;
            yb=0;      
            ks[0] = 0;
            cout << 0 << endl;
            continue;
        } 

        if (c==1) {
            k=0;
            yb=1;
            xe=-1;
            ks[1] = 0;
            cout << 0 << endl;
            continue;
        }

        if (c == 2) {
            if (a[0] == a[1]) {
                k=1;
                ks[c] = k;
                cout << 1 << endl;
                xe=0;
                yb=1;
                
            } else {
                k=0;
                ks[c] = k;
                cout << 0 << endl;
                yb=2;
                xe=-1;
            }
          continue;
        }

        if (op=='-') {
            k= ks[c];
            cout << k << endl;
            continue;
        }

        if (v[ a[c] ] == 1) {
             xe = -1;
             yb = c;
             k=0;
             ks[c] = 0;
             cout << 0 << endl;                   
             continue;
        }
        
        if (a[c-1] == a[xe+1]) {
             k+=1;
             ks[c] = k;
             xe=xe+1;
             cout << k << endl;
            continue;
        }  

        int r;
        loopoo:
        while (k > 0) {
            if (a[k-1] != a[c-1]) {
                k--;
            } else {
                break;
            }
        }

        if (k==0) {
          xe = -1;
          yb = c;
          ks[c] = 0;
          cout << 0 << endl;                   
          continue;
        } 

        int p =0;
        for(p=0; p<k; p++) {
            if ( a[p] != a[c-k+p])
                break;
        }
        if (p==k) {
           xe = k-1;
           yb = c-k;        
           ks[c] = k;
           cout << k << endl;
        } else {
           k--;
           goto loopoo;
        }
    } // for all n
    return 0;
}

