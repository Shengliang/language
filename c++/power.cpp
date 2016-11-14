#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

/* http://www.geeksforgeeks.org/modular-exponentiation-power-in-modular-arithmetic/ */

/* Iterative Function to calculate (x^n)%p in O(logy) */
uint64_t power(uint64_t x, uint64_t y, uint64_t p)
{
    uint64_t res = 1;      // Initialize result
 
    x = x % p;  // Update x if it is more than or 
                // equal to p
 
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res*x) % p;
 
        // y must be even now
        y = y>>1; // y = y/2
        x = (x*x) % p;  
    }
    return res;
}

uint64_t power2(uint64_t x, uint64_t y,  uint64_t p)
{
    uint64_t res = 1;      // Initialize result
 
    x = x % p;  // Update x if it is more than or 
                // equal to p
 
    while (y > 0)
    {
        // If y is odd, multiply x with result
        if (y & 1)
            res = ((res*x)>>1) % p;
 
        // y must be even now
        y = y>>1; // y = y/2
        x = ((x*x)>>2) % p;  
    }
    return res;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int64_t a,b, t;
//    cin >> a >> b >> t;
    printf("%llX\n", 1000000007LL);

for(int r=2; r < 200; r++) 

    int64_t r=a+b;
    if (r&1==0) {
        r>>=1;
        uint64_t res = power(r, t, 1000000007LL);
        cout << res << endl;
    } else {
        uint64_t res = power2(r, t, 1000000007LL);
        cout << res << endl;
    }
    
    return 0;
}
