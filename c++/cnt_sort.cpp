#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    cin >> n;
 
    vector<pair<int, string> > v(n);
    vector<int> h(100, 0);
    for(int i=0; i<n;  i++) {
        int x;
        string str;
        cin >> x >> str;
        v.push_back( pair<int, string>(x,str));
        
        h[x]++;
    }
    int k=0;
    sort(begin(v), end(v));
    for(int t=0; t<100; t++) {
        if (h[t]) {
            int c=h[t];
            k+=c;
            cout << v[k].second << " ";
        } else {
            cout << "- ";
        }
       
    }
    return 0;
}

