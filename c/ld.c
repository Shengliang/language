// gcc -o outfile -Xlinker --defsym -Xlinker key=0x9000 ld.c
// gcc -static -o outfile -Xlinker --defsym -Xlinker key=0x9000 -Wl,--verbose ld.c 
//  size outfile
#include <stdio.h>
extern int key;
int main(void) {
    int stack_d32 = 0;
    printf("&key:%p &stack_d32:%p\n", &key, &stack_d32);
    return 0;
}
