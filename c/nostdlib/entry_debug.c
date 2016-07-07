#include<stdio.h>
#include<stdlib.h>
/*
 * Modify the default entry point.
 * Call entry directly and then exit.
 * $ gcc -e entry -nostdlib entry.c
 * 
 * Ref: https://blogs.oracle.com/ksplice/entry/hello_from_a_libc_free
 */
/* 
 * x84 assembly: suffixes
 * b = byte 8 bit
 * s = short 16 bit
 * w = word 16 bit
 * l = long 32 bit
 * q = quad 64 bit
 * t = ten bytes (80-bit floating point)
 */

static __attribute__((used)) int var1 = 42;
static __attribute__((used)) int count = 66;
int pass(int param)
{
  int out;
  // param += 0x11
  asm("add $0xA,%0" : "+r"(param) :: "cc");
  printf("%d\n", param);

  // move 32 bit %1(param) to %0(out)
  asm("movl %1,%0" : "=r"(out) : "r"(param));
  printf("%d\n", out);

  asm("mov var1,%0" : "=r"(out));
  printf("%d\n", out);
  return out;
}
void entry(void)
{
   count++;
   register int x = pass(count);
   printf("%d %d\n", count, x);
   // exit(count);
   asm volatile("movl %0,var1" :: "r"(count) : "memory");
   printf("%d %d\n", count, var1);
   asm("movl $1,%eax; movl count,%ebx; int $0x80");
}
int main() {
  return 11;
}
