#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
int antiprimes[16] = {1, 2, 4, 6, 12, 24, 36, 48, 60, 120, 180, 240, 360, 720, 840, 1260};
/*
http://www.calculatorsoup.com/calculators/math/prime-factors.php
http://mathworld.wolfram.com/HighlyCompositeNumber.html

2^2 x 3^2 x 5^1 x 7^1 1260
2^4 x 3^1 x 5^1 x 7^1 1680
2^3 x 3^2 x 5^1 x 7^1 2520
2^4 x 3^2 x 5^1 x 7^1 5040
*/
    
void finda(int a, int i, vecotr<int>& arr) {
    int k=1;
    int x=arr[i];
    while (x <= a) {
        x*=arr[i];
        k++;
    }
    
    
}
void query(void) {
    int a;
    cin >> a;
    
    for(int i=0; i<16; i++) {
        if (antiprimes[i] >= a) {
            cout << antiprimes[i] << endl;
            return;
        }
    }
    
    vector<int> arr(10,0);
    for(int i=0; i<10; i++) {
        finda(a, i, arr);
    }
    
    
    
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    for(int i=0; i<n; i++) {
        query();
    }
    return 0;
}

