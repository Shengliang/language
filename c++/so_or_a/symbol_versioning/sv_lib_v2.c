#include<stdio.h>
__asm__(".symver xyz_v1,xyz@VER_1");
__asm__(".symver xyz_v2,xyz@@VER_2");

void xyz_v1(void) { printf("v1 xyz\n"); }
void xyz_v2(void) { printf("v2 xyz\n"); }

void pqr(void) { printf("v2 pqr\n"); }
