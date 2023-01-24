// Compiled with: g++ -Wall -std=c++14 -pthread

#include <iostream>
#include<vector>
#include <algorithm> 

using namespace std;

struct A {
  char            ch;
  char            d[23];
  char*           dd[0];
};

struct B {
  char            ch;
  char            d[23];
  char*           dd[0];
};
/*

stack grow down direction
.
a.d
a.ch == b.d
b.ch

.




^
^
heap 
------


main....
foo
f2....
f1....
text [code]


00000000000000
*/

void f1() {
}
void f2() {
}
int main();
void foo() {
    
    A a,b;
    
    
    //Learned: new(1) to (32) are same == heap usage: 40 bytes = 32 + 8(hidden header)
    
    A *pa = new A();  ///0x20 + 8 = 40 bytes
    B *pb = new B();
    
    for(int i = 0; i < 24; ++i) {
        char *p1 = &(pa->ch);
        char *p2 = &(pb->ch);
        p1[i] = 'A' + i;
        p2[i] = 'a' + i;
    }
    
    /// 0x20 = 32 bytes? why?
    for(int i = 0; i < 40; ++i) {
        uint8_t* p = (uint8_t*) pa;
        uint8_t* q = (uint8_t*) pb;
        char buf[32];
        sprintf(buf, "%02d %p:pa:%02X  %p:pb:%02X\n", i, &p[i-8], p[i-8], &q[i-8], q[i-8]);
        cout << buf <<endl;
    }
    
    cout << "pa:" << pa << " pb:" << pb << endl;
    
    cout << "sizeof(char):" << sizeof(char) << endl; // 1 byte
    cout << "sizeof(char*):" << sizeof(char*) << endl; //8 bytes assume 64 bit CPU;   4 bytes if 32bit CPU.
    cout << "sizeof(A):"    << sizeof(A)    << endl; // 8 bytes, not 1 byte 
    
    cout << "sizeof(B):"    << sizeof(B)    << endl; // 16 bytes
    
    cout << "foo:" << (uint64_t*)foo << " main:" <<(uint64_t*)main << endl;
    cout << "f1:" << (uint64_t*)f1 << " f2:" <<(uint64_t*)f2 << endl;

    if ((uint64_t*)foo < (uint64_t*)main) 
        cout << "foo < main" << endl;
    else 
        cout << "foo >= main" << endl;
        
    cout << "&a.ch:" << (uint64_t*)&a.ch << " &b.ch:" << (uint64_t*)&b.ch << endl;
    cout << "a.d: " << (uint64_t*)a.d << " "  << endl;
    cout << "b.d: " << (uint64_t*)b.d << " "  << endl;
    
}

int main(){
    foo();
    return 0;
}

