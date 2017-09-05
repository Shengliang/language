#include<stdio.h>
#include<stdlib.h>

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

void list_print(struct node_t * r)
{
   while(r) {
      printf("%d %p\n", r->value, r->next);
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

	list_print(list1.head);
	list_print(list2.head);
	return 0;
}
