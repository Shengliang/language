#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdint>
#include <vector>
#include <string>
#include <map>
using namespace std;


#define WHERE(n) printf("%s:%d %p\n", __FUNCTION__, n, this);

string getC(int c){
  return "ABC";
}

void printC(const string& c) { printf("1");}
void printC(const string&& c) { printf("2");}

template<class T> using vec1 = vector<T>;
template<typename T> using vec = vector<T>;

template<typename T> using atype = T;

typedef vector<string> vstr;

class F;
class S {
   // friend  F; // basic class is friend of F. Not enough!
private:
   int pri = 1;
protected:
   int prot = 2;
public:
   int pub = 3;
   S() { WHERE(1); }
   ~S() { WHERE(11); }
   S(S & s) { WHERE(2); }
   S(S && s) { WHERE(3); }
   S& operator=(S& s) { WHERE(4); return *this; }
};

class D : S {
public:
   friend  F; // Need this line.
    void foo() {
        prot = 3;
    }
    void print() {
      // cout << pri << " " << prot << " " << pub << endl;
      cout << __FUNCTION__ ;
      cout << prot << " " << pub << endl;
    }
};

class F {
  public:
   void print(const D &d) {
      cout << d.prot << " " << d.pub << endl;
   }
};

void test(void)
{
   // rvalue reference
   string c = getC(0);
   printC(c);
   printC(getC(1));

   // std::move
   {
     S s1;
     S s2;
     s2 = s1;
   }
   {
     S* p1 = new S;
     S* p2 = new S;
     printf("p1:%p\n", p1);
     printf("p2:%p\n", p2);
  
     // valgrind  --leak-check=full ./a.out
     delete p2;
  
     p2 = move(p1);
     printf("p1:%p\n", p1);
     printf("p2:%p\n", p2);
     delete p2;
   }

   // alias types
   {
      vec<int> v;
      v.push_back(3);
      printf("%d\n", v[0]);
   }
   {
      vec1<int> v;
      v.push_back(3);
      printf("%d\n", v[0]);
   }
   atype<int> a;
   a = 4;
   cout << a << endl;
   vstr vs;
   vs.push_back("me");
   cout << vs[0] << endl;

   // map key
   string k="k";
   string v="v";
   map<string, string> dic;
   dic[k] = v;
   
   auto it = dic.find(k);
   // it->first = 'K'; // error!
   it->second = 'V';
   cout << it->first << " " << it->second << endl;

   // initialization
   int x{3};
   cout << x << endl;

   int arr[3]{4,5,6};
   for(auto & e: arr) {
     cout << e << endl; 
   }

   D d1;
   d1.foo();
   d1.print();
   F f;
   f.print(d1);
}


int main() {
    test();
    return 0;
}
