#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


bool isPrime(int n) {
    if(n==1) return false;
    int x = sqrt(n);
    vector<int> primes = {2};
        //{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 
        //47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
    
    if (std::binary_search (begin(primes), end(primes), n))
        return true;

    int i=0;
    int y=primes.back();
    for(;;) {
       y = (i < primes.size()) ? primes[i] : (y+1);
       if ( y > x ) {
           return true;
       }
       if ((n%y)==0) {
           return false;
       }
       i++;
       cout << x << " " << y << " " << i << endl;
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N;
    cin >> N;
    for(int i=0; i<N; i++) {
        int n;
        cin >> n;
        if (isPrime(n)) {
            cout << n << "Prime" << endl;
        } else {
            cout << n << "Not prime" << endl;
        }
    }
    return 0;
}

