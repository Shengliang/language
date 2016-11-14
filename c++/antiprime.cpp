#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
// Highly Composite Number
int c;
vector<int> arr(10,0);
vector<int> antiprimes = {1, 2, 4, 6, 12, 24, 36};
// vector<int> antiprimes = {1, 2, 4, 6, 12, 24, 36, 48, 60, 120, 180, 240, 360, 720, 840, 1260};
/*
http://www.calculatorsoup.com/calculators/math/prime-factors.php
http://mathworld.wolfram.com/HighlyCompositeNumber.html
http://wwwhomes.uni-bielefeld.de/achim/julianmanuscript3.pdf

2^0       1 
2^1       2 
2^2       4 
2^1 x 3^1 6 
2^2 x 3^1 12 
2^3 x 3^1 24 
2^2 x 3^2 36 
2^4 x 3^1 48 
2^2 x 3^1 x 5^1 60 
2^3 x 3^1 x 5^1 120 
2^2 x 3^2 x 5^1 180 
2^4 x 3^1 x 5^1 240
2^3 x 3^2 x 5^1 360
2^4 x 3^2 x 5^1 720
2^3 x 3^1 x 5^1 x 7^1 840
2^2 x 3^2 x 5^1 x 7^1 1260
2^4 x 3^1 x 5^1 x 7^1 1680
2^3 x 3^2 x 5^1 x 7^1 2520
2^4 x 3^2 x 5^1 x 7^1 5040
                              
2^4   3^2   5^2   7^1  11^1   277200
2^5   3^3   5^1   7^1  11^1   332640
*/
    
//                   2^1  2^2  2*3  2*5  4*3  4*4  2*9  3*7  4*7
int r[10]      = {2, 2,   4,   6,   10,  12,  16,  18,  21,  28};
int primes[10] = {2, 3,   5,   7,   11,  13,  17,  19,  23,  29};
//                0  1    2    3     4    5    6   7    8    9
uint64_t parr(vector<int>& arr, int sz) {
  uint64_t cnt=1;
  for(int i=0; i<sz; i++) {
      cnt *= (arr[i]+1);
  }
  return cnt;
}
int next_hc(int hc, vector<int>& arr) {
    // r=29/28 = 1.036
    if ( (c>=9) &&
         ((arr[1]-1) >= arr[2]) &&
         ((arr[3]-1) >= arr[4]) &&
         ((arr[8]-1) >= arr[9])
       ) {
        uint64_t x = parr(arr, c);
        vector<int>  tarr(arr);
        tarr[9]+=1;
        tarr[3]-=1;
        tarr[1]-=2;
        uint64_t y = parr(tarr, c+(tarr[9]==1));
        if (y>x) {
           arr[9]+=1;
           arr[3]-=1;
           arr[1]-=2;
           
           hc>>=2;
           hc/=primes[3];
           hc*=primes[9];
           if(arr[9] == 1) c++;
           return hc;
        }
    }

    // r=19/18 = 1.056
    if ( (c>=7) &&
         ((arr[1]-2) >= arr[2]) &&
         ((arr[6]-1) >= arr[7])
       ) {
        uint64_t x = parr(arr, c);
        vector<int>  tarr(arr);
          tarr[7]+=1;
          tarr[1]-=2;
          tarr[0]-=1;
        uint64_t y = parr(tarr, c+(tarr[7]==1));
        if (y > x) {
          arr[7]+=1;
          arr[1]-=2;
          arr[0]-=1;
          hc>>=1;
          hc/=primes[1];
          hc*=primes[7];
          if(arr[7] == 1) c++;
          return hc;
        }
    }

    // r=17/16 = 1.0625
    if ( (c>=6) &&
         ((arr[0]-4) >= arr[1]) &&
         ((arr[5]-1) >= arr[6])
       ) {
        uint64_t x = parr(arr, c);
        vector<int>  tarr(arr);
        tarr[6]+=1;
        tarr[0]-=4;
        uint64_t y = parr(tarr, c+(tarr[6]==1));
        if (y > x) {
           arr[6]+=1;
           arr[0]-=4;
           hc>>=4;
           hc*=primes[6];
           if(arr[6] == 1) c++;
           return hc;
        }
    }

    // r=13/12 = 1.08
    if ( (c>=5) &&
         ((arr[0]-1) >= arr[1]) &&
         ((arr[1]-1) >= arr[2]) &&
         ((arr[4]-1) >= arr[5])
       ) {
        uint64_t x = parr(arr, c);
        vector<int>  tarr(arr);
           tarr[5]+=1;
           tarr[1]-=1;
           tarr[0]-=2;
        uint64_t y = parr(tarr, c+(tarr[5]==1));
        if (y>x) {
           arr[5]+=1;
           arr[1]-=1;
           arr[0]-=2;
           hc>>=2;
           hc/=primes[1];
           hc*=primes[5];
           if(arr[5] == 1) c++;
           return hc;
        }
    }

    // r=23/21 = 1.095
    if ( (c>=8) &&
         ((arr[1]-1) >= arr[2]) &&
         ((arr[3]-1) >= arr[4]) &&
         ((arr[7]-1) >= arr[8])
       ) {
        uint64_t x = parr(arr, c);
        vector<int>  tarr(arr);
           tarr[8]+=1;
           tarr[3]-=1;
           tarr[1]-=1;
        uint64_t y = parr(tarr, c+(tarr[8]==1));
        if (y>x) {
           arr[8]+=1;
           arr[3]-=1;
           arr[1]-=1;
           hc/=primes[1];
           hc/=primes[3];
           hc*=primes[8];
           if(arr[8] == 1) c++;
           return hc;
        }
    }

    // r=11/10 = 1.1
    if ( (c>=4) &&
         ((arr[0]-1) >= arr[1]) &&
         ((arr[2]-1) >= arr[3]) &&
         ((arr[3]-1) >= arr[4])
       ) {
        uint64_t x = parr(arr, c);
        vector<int>  tarr(arr);
           tarr[4]+=1;
           tarr[2]-=1;
           tarr[0]-=1;
        uint64_t y = parr(tarr, c+(tarr[4]==1));
        if (y>x) {
           arr[4]+=1;
           arr[2]-=1;
           arr[0]-=1;
           hc>>=1;
           hc/=primes[2];
           hc*=primes[4];
           if(arr[4] == 1) c++;
           return hc;
        }
    }

    // r=10/9 = 1.1111
    // 2*5 /  (3*3)
    // 2 3 5 
    // 0 1 2
    if ( (c>=3) &&
         ((arr[1]-3) >= arr[2])
       ) {
        uint64_t x = parr(arr, c);
        vector<int>  tarr(arr);
           tarr[2]+=1;
           tarr[0]+=1;
           tarr[1]-=2;
        uint64_t y = parr(tarr, c+(tarr[2]==1));
        if (y>x) {
           arr[2]+=1;
           arr[0]+=1;
           arr[1]-=2;
           hc/=primes[1];
           hc/=primes[1];
           hc<<=1;
           hc*=primes[2];
           if(arr[2] == 1) c++;
           return hc;
        }
    }
     
    // r=7/6 = 1.167
    if ( (c>=3) &&
         (arr[0] >= arr[1]) &&
         ((arr[1]-1) >= arr[2]) &&
         ((arr[2]-1) >= arr[3])
       ) {
        uint64_t x = parr(arr, c);
        vector<int>  tarr(arr);
           tarr[3]+=1;
           tarr[1]-=1;
           tarr[0]-=1;
        uint64_t y = parr(tarr, c+(tarr[3]==1));
        if (y>x) {
           arr[3]+=1;
           arr[1]-=1;
           arr[0]-=1;
           hc>>=1;
           hc/=primes[1];
           hc*=primes[3];
           if(arr[3] == 1) c++;
           return hc;
        }
    }

    // 0 1 2 3 4  5  6
    // 2 3 5 7 11 13 17
    // r=20/17 = 1.1765
    if ( (c>=7) &&
         ((arr[0]-4) >= arr[1]) &&
         ((arr[5]-1) >= arr[6])
       ) {
        uint64_t x = parr(arr, c);
        vector<int>  tarr(arr);
           tarr[6]-=1;
           tarr[2]+=1;
           tarr[0]+=2;
        uint64_t y = parr(tarr, c-(tarr[6]==0));
        if (y > x) {
           arr[6]-=1;
           arr[2]+=1;
           arr[0]+=2;
           hc/=primes[6];
           hc*=primes[2];
           hc<<=2;
           if(arr[6] == 0) c--;
           return hc;
        }
    }

    // r=6/5 = 1.2
    if ( (c>=3) &&
         (arr[2] > 1) &&
         ((arr[2]-1) >= arr[3])
       ) {
        uint64_t x = parr(arr, c);
        vector<int>  tarr(arr);
          tarr[2]-=1;
          tarr[1]+=1;
          tarr[0]+=1;
        uint64_t y = parr(tarr, c-(tarr[2]==0));
        if (y>x) {
          arr[2]-=1;
          arr[1]+=1;
          arr[0]+=1;
          hc<<=1;
          hc*=primes[1];
          hc/=primes[2];
          if(arr[2] == 0) c--;
          return hc;
        }
    }
    // r=5/4 = 1.25
    if ( (c>=2) &&
         ((arr[0]-2) >= arr[1]) &&
         ((arr[1]-1) >= arr[2])
       ) {
        uint64_t x = parr(arr, c);
        vector<int>  tarr(arr);
          tarr[2]+=1;
          tarr[0]-=2;
        uint64_t y = parr(tarr, c+(tarr[2]==1));
        if (y>x) {
          arr[2]+=1;
          arr[0]-=2;
          hc>>=2;
          hc*=primes[2];
          if(arr[2] == 1) c++;
          return hc;
        }
    }
    // r=4/3 = 1.333
    if ( (c>=2) &&
         ((arr[1]-1) >= arr[2])
       ) {
        uint64_t x = parr(arr, c);
        vector<int>  tarr(arr);
          tarr[1]-=1;
          tarr[0]+=2;
        uint64_t y = parr(tarr, c-(tarr[1]==0));
        if (y>x) {
          arr[1]-=1;
          arr[0]+=2;
          hc<<=2;
          hc/=primes[1];
          if(arr[1] == 0) c--;
          return hc;
        }
    }
    // r=7/5 = 1.4
    if ( (c>=3) &&
         ((arr[2]-2) >= arr[3])
       ) {
        uint64_t x = parr(arr, c);
        vector<int>  tarr(arr);
          tarr[3]+=1;
          tarr[2]-=1;
        uint64_t y = parr(tarr, c+(tarr[3]==1));
        if (y>x) {
          arr[3]+=1;
          arr[2]-=1;
          hc/=primes[2];
          hc*=primes[3];
          if(arr[3] == 1) c++;
          return hc;
        }
    }
    // r=3/2 = 1.5
    if ( (c>=1) &&
         ((arr[0]-2) >= arr[1])) {
        uint64_t x = parr(arr, c);
        vector<int>  tarr(arr);
          tarr[1]+=1;
          tarr[0]-=1;
        uint64_t y = parr(tarr, c+(tarr[1]==1));
        if (y>x) {
          arr[1]+=1;
          arr[0]-=1;
          hc>>=1;
          hc*=primes[1];
          if(arr[1] == 1) c++;
          return hc;
        }
    }

    // 2 3 5 7 11
    // 0 1 2 3 4
    // r=11/7 = 1.57
    if ( (c>=4) &&
         ((arr[3]-2) >= arr[4])
       ) {
        uint64_t x = parr(arr, c);
        vector<int>  tarr(arr);
           tarr[4]+=1;
           tarr[3]-=1;
        uint64_t y = parr(tarr, c+(tarr[4]==1));
        if (y>x) {
           arr[4]+=1;
           arr[3]-=1;
           hc/=primes[3];
           hc*=primes[4];
           if(arr[4] == 1) c++;
           return hc;
        }
    }
     
    // 0 1 2 3 4
    // 2 3 5 7 11 
    // r=18/11 = 1.64
    if ( (c>=5) &&
         ((arr[4]-1) >= arr[5]) &&
         ((arr[0]-1) >= arr[1])
       ) {
        uint64_t x = parr(arr, c);
        vector<int>  tarr(arr);
           tarr[4]-=1;
           tarr[1]+=2;
           tarr[0]+=1;
        uint64_t y = parr(tarr, c-(tarr[4]==0));
        if (y>x) {
           arr[4]-=1;
           arr[1]+=2;
           arr[0]+=1;
           hc<<=1;
           hc*=primes[1];
           hc*=primes[1];
           hc/=primes[4];
           if(arr[4] == 0) c--;
           return hc;
        }
    }

    // r=5/3 = 1.67
    if ( (c>=2) &&
         ((arr[1]-2) >= arr[2])
       ) {
        uint64_t x = parr(arr, c);
        vector<int>  tarr(arr);
          tarr[2]+=1;
          tarr[1]-=1;
        uint64_t y = parr(tarr, c+(tarr[2]==1));
        if (y>x) {
          arr[2]+=1;
          arr[1]-=1;
          hc/=primes[1];
          hc*=primes[2];
          if(arr[2] == 1) c++;
          return hc;
        }
    }


    arr[0]+=1;
    if(arr[0] == 1) c++;
    hc <<= 1;
    return hc;
}

int query(int a) {
    int sz = antiprimes.size();
    for(int i=0; i< sz; i++) {
        if (antiprimes[i] >= a) {
            return antiprimes[i];
        }
    }
    int hc = antiprimes[sz-1];
    for(;;) {
      hc = next_hc(hc, arr);
      //cout << "new hc:" << hc << endl;
      antiprimes.push_back(hc);
      if (hc >= a) 
         break;
    }
    return hc;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    arr[0]=2;
    arr[1]=2;
    c=2;
    cin >> n;
    for(int i=0; i<n; i++) {
        int a;
        cin >> a;
        int hc = query(a);
       cout << hc << endl;
    }
    return 0;
}

