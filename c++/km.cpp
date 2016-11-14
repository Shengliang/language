// http://stackoverflow.com/questions/4607945/how-to-find-the-kth-smallest-element-in-the-union-of-two-sorted-arrays
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>
#include <inttypes.h>
using namespace std;

int getNthlinear(const int* v1, int s1, const int *v2, int s2, int n)
{
    int ans = 0;
    int i1 = 0;
    int i2 = 0;
    for(int i=0; i<= n; i++) {
        if (i1 < s1 && i2 < s1) {
            if (v1[i1] <= v2[i2]) {
                 ans = v1[i1];
                 i1++;
            } else {
                 ans = v2[i2];
                 i2++;
            }
        } else if (i1 == s1) {
              ans = v2[n-s1];
              break;
        } else if (i2 == s2) {
              ans = v1[n-s1];
              break;
        }
    }
    return ans;
}

// Assume n is less than s1 and s2.
int getNthRecurisive(const int* v1, int s1, const int *v2, int s2, int n)
{
     int ms1 = n/2;
     int ms2 = n - ms1 - 1;
     int m1 = v1[ms1];
     int m2 = v2[ms2];
     if (n==0)
         return min(v1[0], v2[0]);
     if (m1 < m2) {
        return getNthRecurisive(v1+ms1+1, s1-ms1-1, v2, s2, n-ms1-1);
     } else {
        return getNthRecurisive(v1, s1, v2+ms2+1, s2-ms2-1, n-ms2-1);
     }
}

// Assume n is less than s1 and s2.
int getNthLoop(const int* v1, int s1, const int *v2, int s2, int n)
{
     while (n>0) {
         int ms1 = n/2;
         int ms2 = n - ms1 - 1;
         int m1 = v1[ms1];
         int m2 = v2[ms2];
         if (m1 < m2) {
            v1 = v1+ms1+1;
            s1 = s1-ms1-1;
            n  = n-ms1-1;
         } else {
            v2 = v2 + ms2 + 1;
            s2 = s2 - ms2 - 1;
            n  = n  - ms2 - 1;
         }
     }
     return min(v1[0], v2[0]);
}

int getNthlinear(vector<int>& v1, vector<int>& v2, int n)
{
    int x0 = getNthlinear(v1.data(), v1.size(), v2.data(), v2.size(), n);
    int x1 = getNthRecurisive(v1.data(), v1.size(), v2.data(), v2.size(), n);
    int x2 = getNthLoop(v1.data(), v1.size(), v2.data(), v2.size(), n);
    if (x1 != x0) {
        cout << "error:" << x1 << " != " << x0 << endl;
    }
    if (x2 != x0) {
        cout << "error:" << x2 << " != " << x0 << endl;
    }
    return x0;
}

int getNth(vector<int>& v1, vector<int>& v2, int n)
{
   return getNthlinear(v1, v2, n);
}

int test(int *a1, int s1, int *a2, int s2)
{
    int rc = 0;
    vector<int> v1(a1, a1+s1);
    vector<int> v2(a2, a2+s2);
    vector<int> v3(a1, a1+s1);
    for(auto & e : v2) {
        v3.push_back(e);
    }
    sort(begin(v3), end(v3));

    // Assume n is less than s1 and s2.
    int n = min(s1, s2);
    for(int i=0; i<=n; i++) {
       int ith = getNth(v1, v2, i);
       if (ith != v3[i]) {
          printf("% 2d % 2d != % 2d\n", i, ith, v3[i]);
          rc++;
       }
       else {
          printf("% 2d % 2d == % 2d\n", i, ith, v3[i]);
       }
    }
    return rc;
}

#define SZ(arr)  (sizeof(arr)/sizeof(arr[0]))
int test1(void)
{
cout << "test1" << endl;
    int a1[] = {1,2,3,4,5,6,7,8,9};
    int a2[] = {2,4,6,8,10,12,14,16,18};
    return test(a1, SZ(a1), a2, SZ(a2)); 
}

int test2(void)
{
cout << "test2" << endl;
    int a1[] = {1,2,3,4,5};
    int a2[] = {5,6,8,10,12};
    return test(a1, SZ(a1), a2, SZ(a2)); 
}
int test3(void)
{
cout << "test3" << endl;
    int a1[] = {1,2,3,4,5};
    int a2[] = {1,2,3,4,5};
    return test(a1, SZ(a1), a2, SZ(a2)); 
}

int main()  
{  
    test1();
    test2();
    test3();
    return 0;  
}  
