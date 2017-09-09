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


/*
004003e8 <list_tail_append>:    # atomic_exchange(&list->tail, n)
  4003e8:       c0820004        ll      v0,4(a0)  # v0 = list->tail
  4003ec:       00a00825        move    at,a1     # at = a1 = n
  4003f0:       e0810004        sc      at,4(a0)  # list->tail = n
  4003f4:       1020fffc        beqz    at,4003e8 <list_tail_append>
  4003f8:       00000000        nop

  4003fc:       0000000f        sync
  400400:       10400003        beqz    v0,400410 <list_tail_append+0x28> #if old_tail == NULL goto +0x28
  400404:       00000000        nop
  400408:       03e00008        jr      ra
  40040c:       ac450004        sw      a1,4(v0)   # old_tail->next = n
  400410:       03e00008        jr      ra
  400414:       ac850000        sw      a1,0(a0)   # list->head = n

0040041c <list_tail_append>:
  40041c:	c0820004 	ll	v0,4(a0)
  400420:	00a00825 	move	at,a1
  400424:	e0810004 	sc	at,4(a0)
  400428:	1020fffc 	beqz	at,40041c <list_tail_append>
  40042c:	00000000 	nop
  400430:	0000000f 	sync
  400434:	10400009 	beqz	v0,40045c <list_tail_append+0x40>
  400438:	00000000 	nop
  40043c:	c0430004 	ll	v1,4(v0)
  400440:	00a00825 	move	at,a1
  400444:	e0410004 	sc	at,4(v0)
  400448:	1020fffc 	beqz	at,40043c <list_tail_append+0x20>
  40044c:	00000000 	nop
  400450:	0000000f 	sync
  400454:	03e00008 	jr	ra
  400458:	00000000 	nop
  40045c:	c0820000 	ll	v0,0(a0)
  400460:	00a00825 	move	at,a1
  400464:	e0810000 	sc	at,0(a0)
  400468:	1020fffc 	beqz	at,40045c <list_tail_append+0x40>
  40046c:	00000000 	nop
  400470:	0000000f 	sync
  400474:	03e00008 	jr	ra
  400478:	00000000 	nop
type __sync_lock_test_and_set (type *ptr, type value, ...)
Thi is an atomic exchange operation.
It writes value into *ptr, and returns the previous contents of *ptr.
*/
#define atomic_exchange(ptr, value) __sync_lock_test_and_set (ptr, value)

void list_tail_append(struct list_t *list, struct node_t* n)
{
	/* atomically update the tail of the list */
	struct node_t * old_tail = atomic_exchange(&list->tail, n);
	if (old_tail) { /* if the previous tail is not null, then update it. */
		// old_tail->next = n;
	        (void)atomic_exchange(&old_tail->next, n);
	} else {        /* else update the head of the list. */
		// list->head = n;
	        (void)atomic_exchange(&list->head, n);
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
