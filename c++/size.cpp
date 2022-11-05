#include <iostream>
#include <vector>

/* What is sizeof the following struct types? */
struct A {
};

struct B {
    char ch;
};

struct C {
    uint64_t v64;
};

struct D {
    char ch;
    uint64_t v64; 
};

struct E {
    uint64_t v64; 
    char ch;
};

struct F {
    char ch;
    uint32_t data[0];
};

struct G {
    char ch;
    uint32_t data[];
};

struct H {
    char ch; 
    char* data[0];
};

struct I {
    char ch;
    char* data[];
};

#define P(type) std::cout << "sizeof(" << #type << ") = " << sizeof(type) << std::endl;

int main () {

    P(A)
    P(B)
    P(C)
    P(D)
    P(E)
    P(F)
    P(G)
    P(H)
    P(I)

    std::string a;
    std::cout << sizeof(a) << std::endl;
    std::string b = "shengliang.song";
    std::cout << sizeof(b) << std::endl;

    std::string c = "1234567890_1234567890_1234567890_1234567890_";
    std::cout << sizeof(c) << std::endl;
    std::cout << sizeof(char *) << std::endl;
    std::cout << sizeof(std::string) << std::endl;
    std::cout << sizeof(std::string *) << std::endl;
   return 0;
}
