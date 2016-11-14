// https://www.hackerrank.com/challenges/circular-palindromes?h_r=next-challenge&h_v=zen
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

typedef tuple<int, int> str;
map<str, int> h;
int max_len;
const char *s;
#ifdef SSL_DEBUG

string getstr(int off, int k, int len)
{
   string str = "";
   for(int i=0; i< len; i++) {
      str += s[(off+k+i)%max_len];
   }
   return str;
}

void printn(int off, int k, int len)
{
   cout << getstr(s, off, k, len, max_len);
}
#endif

int getAxA(int off, int k, int len)
{
    int a = len&1;
    for(int i=0; i< len/2; i++) {
        if (s[(k+off+i)%max_len] == s[(k+off+len-i-1)%max_len]) {
           a += 2;
        }
        else {
           a = 0;
           break;
        }
    }
    return a;
}

int getn(int off, int k, int len)
{
    if (len <= 1)
       return len;

    auto x = make_tuple(off+k, len);
    if (h.find(x) != h.end()) {
       return h[x];
    }
    int a = getAxA(off, k, len);
    if (a == len) {
       h[x] = a;
       return a;
    }
    int l = getn(off, k, len-1);
    if (len-1 == l) {
       h[x] = l;
       return l;
    }
    int r = getn(off+1, k, len-1);
    if (len-1 == r) {
       h[x] = r;
       return r;
    }
    int b = max(l,r);
#ifdef SSL_DEBUG
    if (a >= b) {
       cout << "A:";
       printn(off,k,len);
       cout << a << endl;
    } else if ( r >= l ) {
       cout << "R:";
       printn(off+1,k,len-1);
       cout << r << endl;
    } else if ( l >= r ) {
       cout << "L:";
       printn(off,k,len-1);
       cout << l << endl;
    } 
#endif
    int ans = max(a,b);
    h[x] = ans; 
    return ans;
}

int main() {
    int num;
    string str;
    cin >> num >> str;
    max_len = str.length();
    s = str.c_str();
    for(int k=0; k < num; k++) {
        int n = getn(0, k, max_len);
        cout << n << endl;
    }
    return 0;
}

