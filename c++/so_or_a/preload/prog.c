#include <stdio.h>

extern void x1();
extern void x2();
extern void x3();
int main() {
    x1();
    x2();
    x3();
    return 0;
}
