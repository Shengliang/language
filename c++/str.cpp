#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

itn periodic()
void test(void)
{
  int n,k;
    string str;
    int a;
    int n1=0,n0=0;
    cin >> n >> k >> str;
    
    //count number zeros.
    for(int i=0; i<str.length(); i++) {
        if (str[i] == '0') n0++;
    }
    //compute number of ones.
    n1 = str.length() - n0;
    
    if (k==0) {
        if (periodic(str))
            return 0;
        else 
            return 1;
    }
    
    a = 1 << k;
    
    cout <<
    
}    

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int t;
    cin >> t;
    for(int i=0; i<t; i++) {
        test();
    }
    return 0;
}
