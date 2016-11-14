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
#ifdef SSL_DEBUG

string getstr(const char* s, int off, int k, int len, int max_len)
{
   string str = "";
   for(int i=0; i< len; i++) {
      str += s[(off+k+i)%max_len];
   }
   return str;
}

void printn(const char* s, int off, int k, int len, int max_len)
{
   cout << getstr(s, off, k, len, max_len);
}
#endif

int getn(const char *s, int off, int k, int len, int max_len)
{
    if (len <= 1)
       return len;

    auto x = make_tuple(off+k, len);
    if (h.find(x) != h.end()) {
       return h[x];
    }

    int a = len&1, b = 0;
    for(int i=0; i< len/2; i++) {
        if (s[(k+off+i)%max_len] == s[(k+off+len-i-1)%max_len]) {
           a += 2;
        }
        else {
           a = 0;
           break;
        }
    }
    int l = getn(s, off, k, len-1,  max_len);;
    int r = getn(s, off+1, k, len-1,  max_len);
    b = max(l,r);
#ifdef SSL_DEBUG
    if (a >= b) {
       cout << "A:";
       printn(s,off,k,len,max_len);
       cout << a << endl;
    } else if ( r >= l ) {
       cout << "R:";
       printn(s,off+1,k,len-1,max_len);
       cout << r << endl;
    } else if ( l >= r ) {
       cout << "L:";
       printn(s,off,k,len-1,max_len);
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
    for(int k=0; k< num; k++) {
        int len=str.length();
        const char *s = str.c_str();
        int n = getn(s, 0, k, len, len);
        //printn(s,0,k,len,max_len);
        cout << n << endl;
    }
    return 0;
}

