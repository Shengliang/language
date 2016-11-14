#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <tuple>
#include <cstdin>

using namespace std;
string str[1000000];

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    cin >> n;
    vector< vector<int> > h(100);
    for(int i=0; i<n;  i++) {
        int x;
        cin >> x >> str[i];
        if (x < 100) {
            h[x].push_back(i);
        } 
    }

    int k = 0;
    for(int t=0; t<100; t++) {
        for(auto i : h[t]) {
            if (e >= 10) {
                cout << str[i] << " ";
            } else  {
                cout << "- ";
            }
        }
    }
    cout << endl;
    return 0;
}

