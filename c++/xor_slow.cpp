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

using namespace std;
//int arr[] = {0,1,3,0,4,1,7,0,8,1,11};


int main(){
    int Q;
    cin >> Q;
    for(int a0 = 0; a0 < Q; a0++){
        long L;
        long R;
        long x=0;
        cin >> L >> R;
        int a=0;
        for(long i = 1; i<L; i++) {
            a^=i;
        }
        for(long i=L; i <=R; i++) {
            a^=i;
            x^=a;
            cout << i << " " << a << " " << x <<endl;;
        }
        cout << x << endl;
    }
    return 0;
}

