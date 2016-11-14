#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdint>
using namespace std;

uint64_t h[100002];
uint64_t S=1,P=0;

void foo() {
    int N;
    cin >> N;
    uint64_t s=0;
    for(int i=0; i<N; i++) {
        uint64_t n;
        cin >> n;
        h[i] = n;
        s+=n;
    }
    sort(h, h+N);
    
    uint64_t m=0;
    for(int i=0; i<N; i++) {
        s-=h[i];
        uint64_t x = 1+(i+1);
        uint64_t y = x*s;
        if (y>m) {
            m=y;
        }
        else {
            break;
        }
    }
    cout << m <<endl;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int T;
    cin >> T;
    for(int i=0; i<T; i++) {
        foo();
    }
    return 0;
}
