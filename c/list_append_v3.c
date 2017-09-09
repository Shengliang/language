#include<stdio.h>
#include<stdlib.h>

typedef unsigned int u32;
typedef unsigned long long u64;

union node_t {
   u64 d64; 
   struct {
	   u32 value;
	   u32 next;
   } s;
};

void node_print(union node_t n) {
	printf("node.d64:%016llX next:%08X value:%d\n", n.d64, n.s.next, n.s.value);
}

union list_t {
   u64 d64;
   struct {
	   u32 head;
	   u32 tail;
   } s;
};

void list_init(union list_t* list)
{
   list->d64 = 0;
}

void list_print(union list_t list, union node_t* nodes)
{
   printf("list.d64:%016llX head:%08X tail:%08X\n", list.d64, list.s.head, list.s.tail);
   u32 next = list.s.head;
   while(next) {
      union node_t n = nodes[next];
      node_print(n);
      next = n.s.next;
   }
}

void list_tail_append(union list_t *list, u32 nID, union node_t* nodes)
{
	if (list->d64 == 0) {
		list->s.head = nID;
		list->s.tail = nID;
	} else {
		union node_t * tail = &nodes[list->s.tail];
		tail->s.next = nID;
		list->s.tail = nID;
	}
}

void list_head_append(union list_t *list, u32 nID, union node_t* nodes)
{
	if (list->d64 == 0) {
		list->s.head = nID;
		list->s.tail = nID;
	} else {
		union node_t * head = &nodes[nID];
		head->s.next = list->s.head;
		list->s.head = nID;
	}
}

int main(void) {
	union list_t list1, list2;
	union node_t arr1[4];
	union node_t arr2[4];
	list_init(&list1);
	list_init(&list2);

	for(int i=0; i< 4; i++) {
		arr1[i].s.value = 100 + i;
		arr1[i].s.next = 0;
		list_tail_append(&list1, i, arr1); 

		arr2[i].s.value = 200 + i;
		arr2[i].s.next = 0;
		list_head_append(&list2, i, arr2); 
	}	

	list_print(list1, arr1);
	list_print(list2, arr2);
	return 0;
}
