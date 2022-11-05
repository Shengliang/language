#include "a.h"
#include <stdio.h>

void default_foo() {
 printf("%s:%s\n", __FILE__, __FUNCTION__);
}
int  main() {
	if (foo)
		foo();
	else 
		default_foo();
	return 0;
}
