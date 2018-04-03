/*
 * gcc stack_or_heap.c -o a.out
 * ./a.out 4
 * ./a.out 4000
 * ./a.out 40000
 * ./a.out 1000000000
 *  What is the max malloc size in your machine?
 */
#include<stdio.h>
#include<stdlib.h>
struct node_t {
   unsigned int value;
   struct node_t *prev;
   struct node_t *next;
};
void print(struct node_t* n) {
   printf("print: %p\n", print);
   printf("&n: %p\n", &n);
   printf("&(n->value): %p\n",   &(n->value));
   printf("&(n->prev): %p\n",    &(n->prev));
   printf(" (n->next): %p\n",     (n->next));
}
 
int main (int argc, char* argv[])  {
        static struct node_t n;
	int cnt = 4;
	if (argc >= 2) {
		sscanf(argv[1], "%d", &cnt);	
		printf("Malloc: %s %d node_t\n", argv[1], cnt);
	}
	struct node_t *p = (struct node_t*) malloc(sizeof(struct node_t)*cnt);
	if (p == NULL) {
		p = &n;
		cnt = 1;
		printf("malloc FAIL.%p %ld=%d*%ld\n", p, cnt*sizeof(struct node_t), cnt, sizeof(struct node_t));
	} else {
		printf("malloc ok.%p %ld=%d*%ld\n", p, cnt*sizeof(struct node_t), cnt, sizeof(struct node_t));
	}
        p->value = 0xFACE;
        p->next  = p;
        p->prev  = p;
        print(p);
	if (p != &n)
		free(p);
        return 0;
}

