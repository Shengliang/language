#include<stdio.h>
#if 0
int my_a __attribute__((weak)) = 10;
int my_b __attribute__((weak)) = 11;
#endif
int my_a  = 10;
int my_b  = 11;

int __attribute__ ((weak)) add(int *pa, int *pb) {
	printf("%s:%s pa:[%p]%d pb:[%p]%d  \n", __FILE__, __FUNCTION__, pa, *pa, pb, *pb);
	return *pa + *pb;
}
int __attribute__ ((weak)) my_default_add(int *pa, int *pb) {
	printf("%s:%s pa:[%p]%d pb:[%p]%d  \n", __FILE__, __FUNCTION__, pa, *pa, pb, *pb);
	return *pa + *pb;
}
