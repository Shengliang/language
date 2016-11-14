#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <list>
using namespace std;

char front(const string& s, int k) {
   return s[k];
}

char back(const string& s, int k) {
   int len = s.length();
   return s[(k+len-1)%len];
}

int printn(const list<char>& wd)
{
   int n = wd.size();
   if (n <= 1) return n;
   list<char> x = wd;
    int a=0, b=0;
    if (x.front() == x.back()) {
     x.pop_front();
     x.pop_back();
     a = 2 + printn(x);
    } else {
        int l,r;
        list<char> ll = wd;
        list<char> lr = wd;
        ll.pop_front();
        lr.pop_back();
        b = max(printn(ll), printn(lr));
    }
    return max(a,b);
}

int main() {
    int num;
    string str;
    cin >> num >> str;
    list<char> wd;
    for(auto ch: str) {
        wd.push_back(ch);
    }
    for(int i=0; i< num; i++) {
        int n = printn(wd);
        cout << n << endl;
        wd.push_back(wd.front());
        wd.pop_front();
    }
    return 0;
}

