#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int64_t dis(int64_t a, int64_t b) {
    return a*a+b*b;
}

int64_t nextx(int64_t a, int64_t b, int64_t y, int64_t* x){
    uint64_t t = (-b*y+1);
    *x = t/a;
    return t%a;
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int q;
    scanf("%d", &q);
    for(int i=0; i<q; i++) {
        int64_t a,b,c;
        scanf("%ld %ld %ld", &a, &b, &c);
        int64_t s=a*a+b*b;
        int64_t xi = a*c;
        int64_t yi = a*b;
    
        if ( (xi%s ==0) && (yi %s == 0)) {
            cout << xi/s << " " << yi/s << endl;
            continue;
        }
        int64_t x = xi/s;
        int64_t y = yi/s;
        int64_t slope = -a/b;
        int64_t dmin=-1;
        int64_t dd = 1;
        cout << 1.0*xi/s << " " << 1.0*yi/s << endl;
        while (dmin==-1) {
            int64_t ax=-1,ay=-1;

            if ( (y-dd)*a%b ==0 ) {
                int64_t d1;
                d1 = dis(x+dd, y-dd);
                if (dmin==-1) {
                    dmin=d1;
                    ax = -(y-dd)*a/b + 1/a;
                    ay = y-dd;
                }
                else if (dmin > d1) {
                    dmin=d1;
                    ax = -(y-dd)*a/b+1/a;
                    ay = y-dd;
                }
            }
            if ( (y+dd)*a%b == 0) {
                int64_t d2;
                d2 = dis(x-dd, y+dd);
                if (dmin==-1) {
                    dmin=d2;
                    ax = -(y+dd)*a/b+1/a;
                    ay = y+dd;
                } 
                else if (dmin >d2) {
                    dmin = d2;
                    ax = -(y+dd)*a/b+1/b;
                    ay = y+dd;
                }
            } 
            if (dmin!=-1) {
                cout << ax << " " << ay << endl;
                break;
            }
            dd+=1;
        } 
    }
    return 0;
}

