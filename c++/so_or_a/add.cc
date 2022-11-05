#include<stdio.h>
int my_a = 20;
int my_b = 21;
int add(int *pa, int *pb) {
	printf("%s:%s pa:[%p]%d pb:[%p]%d  \n", __FILE__, __FUNCTION__, pa, *pa, pb, *pb);
	return *pa + *pb;
}
int my_default_add(int *pa, int *pb) {
	printf("%s:%s pa:[%p]%d pb:[%p]%d  \n", __FILE__, __FUNCTION__, pa, *pa, pb, *pb);
	return *pa + *pb;
}
