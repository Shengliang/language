#include<stdio.h>
#include<stdlib.h>

struct node {
   int v;
   struct node *next;
};

#define N 4
struct node arr[N];

void init(void)
{
   int i = 0;
   for(i=0; i<(N-1); i++) {
      arr[i].v = i;
      arr[i].next = &arr[i+1];
   }
   arr[i].v = i;
   arr[i].next = NULL;
}

void print(struct node * r)
{
   while(r) {
      printf("%d %p\n", r->v, r->next);
      r = r->next;
   }
}

void distribute(struct node * head)
{
	if (!head) return;
	if (!head->next) return;
	if (!head->next->next) return;

        print(head);
        printf("\n");
	struct node* prev = NULL;
	struct node* curr = head;
	while (curr->next) {
		prev = curr;
		curr = curr->next;
	}

	struct node* tempNext = head->next;
	if (head != curr) head->next = curr;
	curr->next = tempNext;
	if (prev) prev->next = NULL;
	distribute(tempNext);
	printf("\n==r===\n");
	print(tempNext);
	printf("\n");
}

int main(void) {
	struct node* root =arr;
	init();
	print(root);
	printf("\n");
	distribute(root);
	print(root);
	return 0;
}
