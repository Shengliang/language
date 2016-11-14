#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdint>

using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    cin >> n;
    int arr[n];
    uint64_t s[n];
    cin >> arr[0];
    s[0]=1;
    for(int i=1; i<n; i++) {
        int t;
        cin >> t;
        arr[i] = t;
        if (t > arr[i-1]) {
            s[i] = s[i-1]+1;
        } else if (t < arr[i-1]) {
            s[i] = 1;
        } else {
            s[i] = s[i-1];
        }
    }
    s[n-1]=1;
    for(int j=n-2;j>=0; j--) {
        
        if (arr[j] >= arr[j+1]) {
            uint64_t t = s[j+1]+1;
            if (j==0) {
               s[j] = max(t,s[j]);
                break;
            }
            if (arr[j] < arr[j-1]) {
                s[j] = max(t,s[j]);
            } else {
                break;
            }
        }
    }
    uint64_t sum=0;
    for(int i=0; i<n; i++) {
        sum+=s[i];
    }
    cout << sum << endl;
    return 0;
}

