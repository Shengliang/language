#include<stdio.h>
#include<stdlib.h>

struct node_t {
   int value;
   struct node_t *next;
};
struct list_t {
   struct node_t *head;
   struct node_t *tail;
   int lock;
};

void list_init(struct list_t* list)
{
   list->head = NULL;
   list->tail = NULL;
}
void list_tail_append(struct list_t* list, struct node_t* n) {
 
        // Check and acquire the lock, if available, else keep on checking
        while (__sync_lock_test_and_set(&list->lock,1));
 
	if (list->tail ==  NULL && list->head == NULL) {
		list->head = n;
		list->tail = n;
	} else {
		list->tail->next = n;
		list->tail = n;
	}
 
        // Release the lock after execution of critical section
        __sync_lock_release(&list->lock);
}
 
void list_free(struct list_t* list) {
     struct node_t* n = list->head;
     while(n) {
 	 struct node_t* f = n;
         n = n->next;
	 printf("free:%p\n", f);
         free(f);
     }
}
 
int main (void)  {
        static struct list_t list;
        list_init(&list);
        struct node_t* n = (struct node_t*) malloc(sizeof(struct node_t));
	n->value = 0xface;
	n->next = NULL;
        printf("new n:%p\n", n);
        list_tail_append(&list, n);
        list_free(&list);;
        return 0;
}

