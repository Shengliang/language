#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdint>

using namespace std;

void psum(uint64_t s[], int n) {
    uint64_t sum=0;
    for(int i=0; i<n; i++) {
        sum+=s[i];
    }
    cout << sum << endl;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    cin >> n;
    int arr[n+1];
    uint64_t s[n+1];
    
    cin >> arr[0];
    s[0]=1;
    if (n==1) {
        cout << 1 << endl;
        return 0;
    }
    int eqcnt=1;
    for(int i=1; i<n; i++) {
        int t;
        cin >> t;
        arr[i] = t;
        if (t== arr[0]) 
            eqcnt++;
        if (t > arr[i-1]) {
            s[i] = s[i-1]+1;
        } else {
            s[i] = 1;
        }
    }
    if (eqcnt==n) {
        cout << 1 << endl;
        return 0;
    }
    
   int j=n-1;
   while ((j>=0) && s[j] > 1)
       j--;

   
   //remove one s[j] =1
   j--;
   for(; j>=0; j--) {    
        if (arr[j] > arr[j+1]  && (s[j]==1) ){
            s[j] = s[j+1]+1;
        }
        if (arr[j] > arr[j+1]  && (s[j]>1) ){
            s[j] = max(s[j+1]+1, s[j]);
        }
    }
    psum(s, n);
    return 0;
}
