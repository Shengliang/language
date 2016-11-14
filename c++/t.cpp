#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdint>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    uint64_t t;
    cin >> t;
    uint64_t x = (t-1)/3 + 1;
    int i;
    for(i=63;  i>= 0; i--) {
        if ( (x & (1LL<<i)) )
            break;
    }
    //cout << i << endl;
    uint64_t a = 3*(1LL<<(i));
    uint64_t b = 3*((1LL<<(i))-1);
    //cout << a << " " << b << " " << a - (t-b) << endl;
    cout << a-(t-b)+1 << endl;;

    
    return 0;
}
