#include<stdio.h>
// https://en.cppreference.com/w/c/language/asm
// http://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html

int add(unsigned int p, unsigned int q) {
  unsigned int sum = 0;
   __asm__ __volatile__("addl  %%ebx,%%eax" :"=a"(sum) :"a"(p), "b"(q));
  return sum;
}

int add2(unsigned int p, unsigned int q) {
  unsigned int sum = 0;
  asm volatile("addl  %%ebx,%%eax" :"=a"(sum) :"a"(p), "b"(q));
  return sum;
}

int main(void) {
   printf("%d\n", add(3,4));
   printf("%d\n", add2(3,4));
   return 0;
}
