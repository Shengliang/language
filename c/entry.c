#include<stdio.h>
#include<stdlib.h>
/*
 * Modify the default entry point.
 * Call entry directly and then exit.
 * $ gcc -e entry entry.c
 * 
 * Call crt1.o:_start then call main.
 * $ gcc entry.c
 */
void entry(void)
{
   printf("In entry function.\n");
   exit(0);
}

int main(void) 
{
   printf("In main.\n");
   return 0;
}
