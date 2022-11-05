#include<stdio.h>

extern int add(int*,int*) __attribute__ ((weak_import));

int my_a __attribute__((weak)) = 1;
int my_b __attribute__((weak)) = 2;

int __attribute__ ((weak)) my_default_add(int *pa, int *pb) 
{
	printf("%s:%s week pa:[%p]%d pb:[%p]%d  \n", __FILE__, __FUNCTION__, pa, *pa, pb, *pb);
	return *pa+*pb;
}

int main(void) {
	if (add) 
		return add(&my_a,&my_b);
	else
		return my_default_add(&my_a,&my_b);
}
