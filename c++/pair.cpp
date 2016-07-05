#include<iostream>
#include<utility>
#include<cstdint>
using namespace std;
struct S {
  int64_t a;
  int64_t b;
  S(int64_t _a=0, int64_t _b=0) : a(_a), b(_b) { }
  S& operator+=(const S & other) {
    a += other.a;
    b += other.b;
  }
};
int main(void) {
    pair<uint64_t, uint64_t> a;
    S s1,s2;
    cout << sizeof(s1) << " " << s1.a << " " << s1.b << endl;
    s1 =  { 1,2}; 
    s2 =  { -1,-2}; 
    cout << sizeof(s1) << " " << s1.a << " " << s1.b << endl;
    cout << sizeof(s2) << " " << s2.a << " " << s2.b << endl;
    s1 += s2;
    cout << sizeof(s1) << " " << s1.a << " " << s1.b << endl;
    cout << sizeof(a) << " " << a.first << " " << a.second << endl;
    return 0;
}
