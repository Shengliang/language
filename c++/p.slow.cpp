// https://www.hackerrank.com/challenges/circular-palindromes?h_r=next-challenge&h_v=zen
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <list>
#include <unordered_map>

using namespace std;

unordered_map<pair<char*, int>, int> h;

int getn(char* s, int len)
{
    if (len <= 1)
       return len;

    pair<char*, int> k(s, len);
    if (h.find(k) != end(h)) {
       return h[k];
    }

    int a = len&1, b = 0;
    for(int i=0; i< len/2; i++) {
        if (s[i] == s[len-i-1]) {
           a += 2;
        }
        else {
           a = 0;
           break;
        }
    }
    int l = getn(&s[0], len-1);;
    int r = getn(&s[1], len-1);
    b = max(l,r);
    b= max(a,b);
    h[k] = b; 
    return b;
}

int main() {
    int num;
    string str;
    cin >> num >> str;
    for(int k=0; k< num; k++) {
        int len=str.length();
        char buf[len];
        for(int i=0; i<len; i++) {
          buf[i] = str[(k+i)%len];
        } 
        int n = getn(buf, len);
        cout << n << endl;
    }
    return 0;
}

