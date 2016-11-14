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

int Miss[100001];

int main(){
    int n;
    int k;
    cin >> n >> k;
    for(auto & e: Miss) { e = 0; }
    
    string num;
    cin >> num;
    int ck=0;

    for(int i=0; i< (n/2); i++) {
        if (num[i] != num[n-1-i]) {
            ck++;  
            Miss[i] = 1;
            Miss[n-1-i]=1;
            num[n-1-i] = num[i] = max(num[i], num[n-1-i]);
        }

        if (ck > k) {
            cout << -1 << endl;
            return  0;
        }
    }
    int dk = k - ck;
    for(int i=0; i<= (n/2); i++) {
        if (num[i] == '9')
            continue;
        if (dk==0)
            break;    
        if (Miss[i]) {
            dk--;
            num[n-1-i] = num[i] = '9';
        } else {
            if (dk>=2) {
                 dk-=2;
                 num[n-1-i] = num[i] = '9';
            } 
            else if (dk==1) {
               if(n&1) {
                 dk-=1;
                 num[n/2] = '9';
               } else {
                 break;    
               }
            }
        }
    }
    cout << num;
    
    return 0;
}
