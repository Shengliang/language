// https://www.hackerrank.com/challenges/array-splitting

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdint>
using namespace std;

uint64_t N[16*1024+1];
uint64_t L[16*1024+1];
uint64_t R[16*1024+1];
int n;

int opt(int i, int j) {
    int k=0;
    uint64_t s;
    if(i==j) return 0;
    if(i==0) s=L[j];
    if(j==(n-1)) s=R[i];
    else s = R[0] -L[i-1] - R[j+1];
    if (s==0) {
       //cout << "s0: " << j-i <<  endl;
       return j-i;
    }
    if (s&1) return 0;
#if 0
    for(int m=i; m<=j; m++) {
      cout << N[m] << " ";
    } 
    cout << " s:" << s << endl;
#endif

    uint64_t t = L[i-1]+(s>>1);
    //cout << "f:" << t << endl;
    uint64_t* p = find(L+i, L+j+1, t);
    if (p == (L+j+1)) {
        return 0;
    }
    else {
        k=p-L;
    }
    //cout << "k:" << k << endl;
    //cout << "(" << i << "," << k<<")" << endl;
    
    int o1 = opt(i,k);
    //cout << "(" << k+1 << "," << j<< ")" << endl;
    int o2 = opt(k+1,j); 
    return 1 + max(o1,o2);
}

int foo() {

    cin >> n;
    uint64_t s=0;
    for(int i=0; i<n; i++) {
        uint64_t t;
        cin >> t;
        s+=t;
        L[i] = s;
        //cout << L[i] << " ";
        N[i] = t;     
    }
    //cout << endl;
    if (s==0) {
        return n-1;
    }
    if (s&1) {
        return 0;
    }
    uint64_t hs=(s>>1);
    int k=-1;
    for(int i=0; i<n; i++) {
        R[i] = s;
        s-= N[i];
        // cout << R[i] << " ";
        if (s==hs) {
            k=i;
        }
    }
    //cout << endl;
    if (k==-1) {
        //cout << "z1 here" << endl;
        return 0;
    }
    //cout << "K:" << k << endl;
    return 1+max(opt(0,k), opt(k+1, n-1));
}
int main() {
    int T;
    cin >> T;
    for(int i=0; i<T; i++) {
        cout << foo() << endl;
    }
    return 0;
}
