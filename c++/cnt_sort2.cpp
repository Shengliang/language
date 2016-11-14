#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <tuple>

using namespace std;

typedef tuple<int, string, int> pisi;

bool cmp (pisi i, pisi j)  { return get<0>(i) < get<0>(j); }

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    cin >> n;
    vector<pisi> v;
    vector<int> h(100, 0);
    for(int i=0; i<n;  i++) {
        int x;
        string str;
        cin >> x >> str;
        v.push_back( pisi(x,str, i));
        if (x < 100) {
            h[x]++;
        } 
     
    }
    /*
    stable_sort(begin(v), end(v),cmp);
    for(auto & e: v) {
        if (get<2>(e) >=10) 
        cout << get<1>(e) << " ";
        else
        cout << "- ";
    }
    cout << endl;
    */

    int k = 0;
    for(int t=0; t<100; t++) {
        if (h[t]) {
            int cnt=h[t];
            k+=cnt;

            for(int c=0; c<cnt; c++) cout << k << " ";

        }
       
    }
    cout << endl;
    return 0;
}
