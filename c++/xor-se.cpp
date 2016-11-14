#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

#include <cstdint>


using namespace std;
//uint64_t arr[] = {0,1,3,0,4,1,7,0,8,1,11};

// 0:0 1:1 2:3 3:0 
// 4:4 5:1 6:7 7:0 
uint64_t xor2n(uint64_t n)
{
    switch(n%4) {
         case 0: return n;
         case 1: return 1;
         case 2: return n+1;
         case 3: return 0;
    }
}

// 1:1 3:2 5:7 7:0 
// 9:9 11:2 13:15 15:0 

// 0:0 2:2 4:6 6:0 
// 8:8 10:2 12:14 14:0 
uint64_t xor2nBy2(uint64_t n)
{
    switch((n>>1)%4) {
         case 0: return n;
         case 1: return 2;
         case 2: return n+2;
         case 3: return 0;
    }
}


int main(){
    int Q;
    cin >> Q;
    for(int a0 = 0; a0 < Q; a0++){
        long L;
        long R;
        cin >> L >> R;
        long a=0;
        
        if ((R-L)&1) { //even columns
           a = xor2nBy2(R) ^ xor2nBy2(L-1);
        } 
        if (((R-L)&1) == 0) {   
           a = xor2n(L) ^ xor2nBy2(R) ^ xor2nBy2(L);
        }
        cout << L << " " << R << " " << a << endl;
    }
    return 0;
}

