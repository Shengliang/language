#define DEBUG 0
#if DEBUG
#include<stdio.h>
#endif

#ifndef NULL
#define NULL 0
#endif

struct node_t {
   int value;
   struct node_t *next;
};

struct list_t {
   struct node_t *head;
   struct node_t *tail;
};

void list_init(struct list_t* list)
{
   list->head = NULL;
   list->tail = NULL;
}

typedef void (*func_t)(void* ctx, struct node_t* n);

#if DEBUG
void nprint(void* ctx, struct node_t* n) {
	fprintf((FILE*)ctx, "n:%d %p\n", n->value, n->next);
}
#endif

void nsum(void* ctx, struct node_t* n) {
	int* p = (int*)ctx;
	*p += n->value;
}

void list_op(struct node_t * r, func_t op, void* ctx)
{
   while(r) {
      op(ctx, r);
      r = r->next;
   }
}


void list_tail_append(struct list_t *list, struct node_t* n)
{
	if (list->tail ==  NULL && list->head == NULL) {
		list->head = n;
		list->tail = n;
	} else {
		list->tail->next = n;
		list->tail = n;
	}
}

void list_head_append(struct list_t *list, struct node_t* n)
{
	if (list->tail ==  NULL && list->head == NULL) {
		list->head = n;
		list->tail = n;
	} else {
		n->next = list->head;
		list->head = n;
	}
}

int main(void) {
	struct list_t list1, list2;
	struct node_t arr1[4];
	struct node_t arr2[4];
	int sum1 = 0;
	int sum2 = 0;
	list_init(&list1);
	list_init(&list2);
	for(int i=0; i< 4; i++) {
		arr1[i].value = i;
		arr1[i].next = NULL;
		list_tail_append(&list1, &arr1[i]); 

		arr2[i].value = i;
		arr2[i].next = NULL;
		list_head_append(&list2, &arr2[i]); 
	}	

#if DEBUG
	list_op(list1.head, nprint, stdout);
	list_op(list2.head, nprint, stderr);
#endif

	list_op(list1.head, nsum, &sum1);
	list_op(list2.head, nsum, &sum2);
	return (sum1 == sum2);
}
