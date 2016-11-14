#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdint>
using namespace std;

void foo(){
    int N;
    cin >> N;
    int P[N];
    int W[N];
    uint64_t m=0;
    int mi=-1;
    vector<int> mv;
    
    int l = 0;
    for(int i=0; i<N; i++) {
        int t;
        cin >> t;
        P[i] = t;
        
        if (i==0) {
            l = 0;
            continue;
        }
            
        if (P[i] > P[i-1]) {
            l++;
           if(i==(N-1)) mv.push_back(i);  
        } else if (P[i] < P[i-1]) {
            l--;
            if (mv.size()>0) {
                int j=mv.back();
                if (P[j] < P[i-1]) {
                    mv.back() = i-1;
                } else if (j < (i-2)) {
                    cout << j << " " << (i-2) << endl;
                    mv.push_back(i-1);  
                }
            } else {
               mv.push_back(i-1);  
            }
           
        } else {
            // l no change
        }
    }
    
    uint64_t ms=0;
    int si=0;
    for(int m=0; m<mv.size(); m++) {
        int j=mv[m];
        if(j==0) continue;
        uint64_t s = (j-si)*P[j];
        for(int i=si; i<j; i++) {
            s-=P[i];
        }
        ms+=s;
        si=j+1;
    }
    cout << ms << endl;
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

