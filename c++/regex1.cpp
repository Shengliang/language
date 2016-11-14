#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <regex>
using namespace std;


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int N;
    cin >>N;
    vector<string> v;
    for (int i=0; i<N; i++) {
        string s,e;
        cin >> s;
        cin >> e;
        if (regex_match (e, regex("[a-z.]+?@gmail[.]com") ))
            v.push_back(s);
        if (regex_match (e, regex("[a-z.]+@gmail\\.com") ))
            v.push_back(s);
    }
    sort(begin(v), end(v));
    for(const auto& e: v) {
        cout << e << endl;
    }
    return 0;
}
