#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef unsigned int uint32;
typedef unsigned long long uint64;

//Ref: http://developer.classpath.org/doc/java/util/Random-source.html
class Random
{
private:
   uint64 seed;
public:
   Random() { }

   void setSeed(uint32 seed_) {
     seed = (seed_ ^ 0x5DEECE66D) & ((1LL << 48) - 1);
   }

   uint32 next1000() {
      uint32 bits, val;
      seed = (seed * 0x5DEECE66D + 0xB) & ((1LL << 48) - 1);
      bits = (uint32)(seed >> 17);
      val = bits % 1000;
      return val;
   }
};


int main() {
    int num;
    cin >> num;
    for(int i = 0; i< num; i++) {
        int arr[10];
        int tmp[10];
        int t0, t1;
        cin >> t0 >> t1;
        for(int c =0; c<10; c++) {
           cin >> arr[c];
        }
        int ti;
        Random rand;
        for(ti=t0; ti<t1; ti++) 
         {
           rand.setSeed(ti);
           int cnt=0;
           for(int i=0; i<10; i++) {
             uint32 r = rand.next1000();
             tmp[i] = r;
             if(tmp[i] == arr[i]) cnt++;
           }
           if (cnt==10) {
               break;
           }
        }
        cout << ti << " ";
        for(int i=0; i<10; i++) {
            uint32 r = rand.next1000();
            cout << r;
            if (i<9) cout << " ";
            else cout << endl;
        }
    }
    return 0;
}

