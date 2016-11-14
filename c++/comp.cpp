#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdint>
using namespace std;


void power1(int32_t a, int64_t k, int32_t m) {
 int64_t P;
 int64_t x = a;
 int64_t n = k;
 while ((n & 1) == 0) {
     x = x * x;
     x %= m;
     n >>= 1;
 }
 P = x % m;
 n >>= 1;
 while (n > 0) {
     x = x * x;
     x %= m;
     if ((n & 1) != 0) {
        P = P * x;
        P %=m;
     }
     n >>= 1;
 }
 cout << P << " " << 0 << endl;
}


struct Complex
{
public:
    int64_t a;
    int64_t b;
    int64_t m;
    Complex(int64_t _a, int64_t _b, int64_t _m) : a(_a), b(_b), m(_m) { }
    void square(void) {
        int64_t r1 = (a*a)%m;
        int64_t r2 = (b*b)%m;
        int64_t i = 2*a%m;
        i *=b;
        i %=m;
        a = (r1-r2) % m;
        if (a<0) a += m;
        b = (i) % m;
    }
    void multiply(Complex & c) {
        int64_t r1 = a*c.a%m;
        int64_t r2 = b*c.b%m;
        int64_t i1 = b*c.a%m;
        int64_t i2 = a*c.b%m;
        a = (r1-r2) % m;
        if (a<0) a += m;
        b = (i1+i2) % m;       
    }
};
ostream & operator<<(ostream & out, const Complex& c) {
    out << c.a << " " << c.b;
    return out;
}

// (a+bi)(a+bi) = (a*a  - b*b) + 2ab*i
void power2(int32_t a, int32_t b, int64_t k, int32_t m) 
{
 Complex x(a,b,m);
 int64_t n = k;
 while ((n & 1) == 0) {
     x.square();
     n >>= 1;
 }
 Complex P = x;
 n >>= 1;
 while (n > 0) {
     x.square();
     if ((n & 1) != 0)
        P.multiply(x);
     n >>= 1;
 }
 cout << P << endl;
}

void power(int32_t a, int32_t b, int64_t k, int32_t m)
{
    if (b==0)
        power1(a,k,m);
    else 
        power2(a,b,k,m);
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    int32_t a,b,m;
    int64_t k;
    scanf("%d", &n);
    for(int i=0; i<n; i++) {
        scanf("%d %d %ld %d", &a,&b,&k,&m);
        power(a,b,k,m);
    }
    return 0;
}
