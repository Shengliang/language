// https://www.hackerrank.com/challenges/circular-palindromes?h_r=next-challenge&h_v=zen
#include <cmath>
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <map>

#define MAXN 500000
using namespace std;

int max_len;
const char* s;
char Tbuffer[2*MAXN+4];
int  Pbuffer[2*MAXN+4];

//Ref: http://articles.leetcode.com/longest-palindromic-substring-part-ii 
// Store intermediate result in an array P, 
// where P[i] equals to the length of the palindrome centers at Ti.
// The longest palindromic substring would then be the maximum element in P.


// Transform S into T.
// For example, 
// S     = "abba"       N
// M     = ^.a.b.b.a.$  2N+3
//         01.3.5.7.9.
// T,k0  = ^.a.b.b.a.$
//    i  = 0123456789.
int pre_process(int k, int N) {
  int i;
  Tbuffer[0]     ='^';
  for (i = 0; i < N; i++) {
    Tbuffer[2*i+1] = '.';
    Tbuffer[2*i+2] = s[(k+i)%N];
  }
  Tbuffer[2*N+1] = '.';
  Tbuffer[2*N+2] = '$';
  Tbuffer[2*N+3] = '\0';
  return 2*N+3;
}
 
int longestPalindrome(int k, int len) {
  int n = pre_process(k, len);
  char*T = &Tbuffer[0];
  int *P = &Pbuffer[0];
  int C = 0, R = 0;

  // len = 4
  // n = 2*4-1 = 7
  // T,k0  =  a.b.b.a
  //    i  =  0123456
  //    P0 =  1
  for (int i = 1; i < n-1; i++) {
    //----------i--c--i--------------
    //         012345678 
    //          1 = 4 - (7-4) = 2*4-7 = 1
    int i_mirror = 2*C-i; // equals to i' = C - (i-C)
    
    P[i] = (R > i) ? min(R-i, P[i_mirror]) : 0;
    
    // Attempt to expand palindrome centered at i
    while (T[i + 1 + P[i]] == T[i - 1 - P[i]]) {
      P[i]++;
    }
 
    // If palindrome centered at i expand past R,
    // adjust center based on expanded palindrome.
    if (i + P[i] > R) {
      C = i;
      R = i + P[i];
    }
  }

#if 1
  printf("T: ");
  for(int i = 0; i < n-1; i++) {
    printf("%c  |", T[i]);
  }
  cout << endl;
  printf("P: ");
  for (int i = 0; i < n-1; i++) {
    printf("%02d |", P[i]);
  }
  cout << endl;
#endif
 
  // Find the maximum element in P.
  int maxLen = 0;
  for (int i = 0; i < n-1; i++) {
    if (P[i] > maxLen) {
      maxLen = P[i];
    }
  }
  return maxLen;
}

int main() {
    int num;
    string str;
    cin >> num >> str;
    max_len = str.length();
    s = str.c_str();
    for(int k=0; k < num; k++) {
        int n = longestPalindrome(k, max_len);
        cout << n << endl;
    }
    return 0;
}

