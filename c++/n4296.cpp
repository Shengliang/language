/* reference:
 * Download the November 2014 working draft (free). 
 * http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2014/n4296.pdf 
 */
#include<stdio.h>
#include<iostream>
#include<cstdlib>
#include<algorithm>
using namespace std;

#define WHERE() printf("%s\n", __FUNCTION__)

void argfunc(int i, int j) {
   printf("%d %d\n", i, j);
}

void point_of_declaration(void)
{
     unsigned char x = 12;
     const unsigned char c = 12; {  
        unsigned char x = x;
        printf("%d\n", x); // indeterminate value
        unsigned char c = c;
        printf("%d\n", c); // indeterminate value
     }
     {
          int c[c];
          // print array c size
          printf("%ld\n", sizeof(c)/sizeof(c[0])) ; //output 12
     }
}

#define D(v) printf(#v " :%d\n", v);
void g(int i, int* v) {
   i = v[i++];
   D(i)
   i = 7, i++, i++;
   D(i)
   i = i++ + 1;
   D(i)
   i = i + 1;
   D(i)
   argfunc(i++, i++); 
}

namespace N {
   int i;
   int g(int a) { return a;}
   int j();
   void q();
}
namespace { int l=1; }

namespace N {
    int g(char a) { return l+a; }
    int j();  // OK: duplicate function declaration
    int j() { return g(i); }
    // int i; // error: duplicate definition
    // int q(); // error different return type
}
     
namespace A {
 typedef char* T;
}
namespace B {
 typedef long T;
}
struct Y {
    A::T a;
    B::T b;
};

typedef int f;
namespace X {
   struct A {
      friend int f(A &) { return sizeof(A)+1000; }
      operator int() { return sizeof(A)+9000; }
      void g(A a) { 
          int i = f(a);
          printf("X::sa.g.i %d\n", i); //output 9001, not 1001 
      }
   } sa;
}

namespace N55 {

struct B {
 virtual void f() { WHERE(); }
 B*  mutate(); 
 virtual ~B() { WHERE(); }
};
struct D1 : B { 
   void f() { WHERE(); }
   ~D1() { WHERE(); }
};
struct D2 : B { 
   void f() { WHERE(); }
   ~D2() { WHERE(); }
};

B* B::mutate() {
   WHERE();
   printf("this: %p\n", this);
   D2* d2 = new (this) D2;
   f();
   printf("this: %p\n", this);
   printf("d2: %p\n", d2);
   return d2;
}

void test_g(void) {
   void *p = malloc(sizeof(D1) + sizeof(D2));
   printf("p:%p\n", p);
   B* pb = new(p) D1;
   B* pc = pb->mutate();
   printf("pb: %p\n", pb);
   printf("pc: %p\n", pc);
   void *q = pb;
   pb->f(); 
   pc->f(); 
   // delete pb;
   delete pc;
}

}
    

namespace L {
// 5.1.2 lambda expressions
  void abssort(float* x, unsigned N) {
      sort(x, x+N, [](float a, float b) { return abs(a) < abs(b); });
  }
  void test(void) {
     float farr[] = { -1, 2, -3 };
     abssort(farr, 3);
     // error: deducing return type from braced-init-list
     // auto f2 = [] { return {1,2}; }; 
     int cnt = 1;
     // typo ? 
     // auto f3 = [&cnt]()->int&& { return cnt; };
     auto f3 = [&cnt]()->int& { return cnt; };
     auto & x = f3();
     cout << "cnt:" << cnt << endl;
     cout << "x:" << ++x << endl;
     cout << "cnt:" << cnt << endl;
  }
};
int main(void)
{
   int vec[10];
   int i = 10;
   for(auto & e: vec)  e = 100 + --i;
   for(auto e: vec)  printf("%d ", e);
   printf("\n");
   D(i)
   g(i, vec);
   point_of_declaration();
   X::sa.g(X::sa);
   N55::test_g();
   L::test();
   return 0;
}
