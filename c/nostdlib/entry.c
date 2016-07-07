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

static __attribute__((used)) int count = 41;
void entry(void)
{
   count++;
   asm("movl $1,%eax; movl count,%ebx; int $0x80");
}
int main() {
  return 77; 
}
