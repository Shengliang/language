#include<stdio.h>
#include<stdlib.h>

struct node_t {
   unsigned int value;
   struct node_t *next;
};


void print(struct node_t* n) {
   printf("print: %p\n", print);
   printf("&n: %p\n", &n);
   printf("&(n->value): %p\n",   &(n->value));
   printf("&(n->next): %p\n",    &(n->next));
   printf(" (n->next): %p\n",     (n->next));
}
 
int main (void)  {
        struct node_t* n = (struct node_t*) malloc(sizeof(struct node_t));
	n->value = 0xFACE;
	n->next  = n;
	print(n);
	free(n);
        return 0;
}

