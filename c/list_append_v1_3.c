
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
https://gcc.gnu.org/onlinedocs/gcc/_005f_005fatomic-Builtins.html
004003ec <list_tail_append>:
  // const int mem_ord = __ATOMIC_RELAXED;
  4003ec:	c0820004 	ll	v0,4(a0)   #v0 = list->tail
  4003f0:	00a00825 	move	at,a1      #at = a1 = n
  4003f4:	e0810004 	sc	at,4(a0)   #list->tail =n
  4003f8:	1020fffc 	beqz	at,4003ec <list_tail_append>
  4003fc:	00000000 	nop
  400400:	10400004 	beqz	v0,400414 <list_tail_append+0x28>
  400404:	00000000 	nop
  400408:	ac450004 	sw	a1,4(v0)  #old_tail->next = n
  40040c:	03e00008 	jr	ra
  400410:	00000000 	nop
  400414:	ac850000 	sw	a1,0(a0)  #list->head = n
  400418:	03e00008 	jr	ra
  40041c:	00000000 	nop

// const int mem_ord = __ATOMIC_SEQ_CST;
0040040c <list_tail_append>:
  40040c:	0000000f 	sync
  400410:	c0820004 	ll	v0,4(a0)
  400414:	00a00825 	move	at,a1
  400418:	e0810004 	sc	at,4(a0)
  40041c:	1020fffc 	beqz	at,400410 <list_tail_append+0x4>
  400420:	00000000 	nop
  400424:	0000000f 	sync
  400428:	0000000f 	sync
  40042c:	10400005 	beqz	v0,400444 <list_tail_append+0x38>
  400430:	00000000 	nop
  400434:	ac450004 	sw	a1,4(v0)
  400438:	0000000f 	sync
  40043c:	03e00008 	jr	ra
  400440:	00000000 	nop
  400444:	ac850000 	sw	a1,0(a0)
  400448:	0000000f 	sync
  40044c:	03e00008 	jr	ra
  400450:	00000000 	nop
*/

void list_tail_append(struct list_t *list, struct node_t* n)
{
        /* atomically update the tail of the list */
	// const int mem_ord = __ATOMIC_RELAXED;
	const int mem_ord = __ATOMIC_SEQ_CST;
        struct node_t * old_tail;
	__atomic_exchange(&list->tail, &n, &old_tail, mem_ord);
        if (old_tail) { /* if the previous tail is not null, then update it. */
                // old_tail->next = n;
                __atomic_store(&old_tail->next, &n, mem_ord);
        } else {        /* else update the head of the list. */
                // list->head = n;
                __atomic_store(&list->head, &n, mem_ord);
        }
}

/*
https://libcxx.llvm.org/atomic_design_a.html
00400454 <list_tail_append_acq>:
  400454:	0000000f 	sync
  400458:	c0820004 	ll	v0,4(a0)
  40045c:	00a00825 	move	at,a1
  400460:	e0810004 	sc	at,4(a0)
  400464:	1020fffc 	beqz	at,400458 <list_tail_append_acq+0x4>
  400468:	00000000 	nop
  40046c:	0000000f 	sync
  400470:	10400004 	beqz	v0,400484 <list_tail_append_acq+0x30>
  400474:	00000000 	nop
  400478:	ac450004 	sw	a1,4(v0)
  40047c:	03e00008 	jr	ra
  400480:	00000000 	nop
  400484:	ac850000 	sw	a1,0(a0)
  400488:	03e00008 	jr	ra
  40048c:	00000000 	nop
*/
void list_tail_append_acq(struct list_t *list, struct node_t* n)
{
        /* atomically update the tail of the list */
	const int mem_ord = __ATOMIC_RELEASE;
        struct node_t * old_tail;
	__atomic_exchange(&list->tail, &n, &old_tail, mem_ord);
        if (old_tail) { /* if the previous tail is not null, then update it. */
                // old_tail->next = n;
                __atomic_store(&old_tail->next, &n, mem_ord);
        } else {        /* else update the head of the list. */
                // list->head = n;
                __atomic_store(&list->head, &n, mem_ord);
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
