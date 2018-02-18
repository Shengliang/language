#include <stdio.h>
#include <stdint.h>

const char private_msg[] = "PASSWORD1234567";

char T[4096*256];
char t[8];

char Func1(char n)
{
   char y = 0;
   if ( n < 8){
       y = T[t[n]*4096];
   }
   return y;
}

char Func4(int n)
{
   char y = 0;
   if ( n < 8){
       y = T[t[n]*4096];
   }
   return y;
}

char Func8(uint64_t n)
{
   char y = 0;
   if ( n < 8) {
       y = T[t[n]*4096];
   }
   return y;
}

int main(void)
{
    // printf("s:%s\n", private_msg);
    printf("s:%s\n", (char*)(T-176));
    printf("s:%p\n", private_msg);
    printf("X:%ld\n", T - private_msg);
    printf("T:%p\n", T);
    printf("t:%p\n", t);
    printf("f:%p\n", Func8);
    printf("m:%p\n", main);
    printf("%d\n", Func1(8));
    printf("%d\n", Func4(8));
    printf("%d\n", Func8(8));
    return 0;
}



