/*
 * =============================================================================
 *
 *       Filename:  swap16.c
 *
 *    Description:  swap 8 bytes
 *
 *        Version:  1.0
 *        Created:  03/13/2017 22:03:16
 *       Revision:  none
 *       Compiler:  gcc -g
 *
 *         Author:  Sheng-Liang Song (ssl), sheng-liang.song@sjsu.edu
 *   Organization:  
 *
 * =============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 2
void print(uint32_t* a) {
	printf("\n%p %p\n", a, &a);
	for(int i=0; i<N; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}

void swap8byte(uint32_t* p1, uint32_t* p2)
{       
        for (int i=0; i<N; i++) {
           uint32_t x1 = *p1;
           uint32_t x2 = *p2;
           *p1++ =  x2;
           *p2++ =  x1;
        }
}
uint32_t a[] = {1, 2};
void test(void) {
     uint32_t *b = (uint32_t*)malloc(2*sizeof(uint32_t));
     b[0]='a';
     b[1]='b';
     swap8byte(a, b);
     print(a);
     print(b);
     free((void*)b);
}

int main(int argc, char* argv[])
{
	test();
	return 0;
}

