#include<stdio.h>
#include<stdlib.h>

typedef unsigned int u32;
typedef unsigned long long u64;

#define VALUE(n) n.id[0]
#define NEXT(n) n.id[1]
union node_t {
   u64 d64; 
   u32 id[2];
};

void node_print(union node_t n) {
	printf("node.d64:%016llX next:%08X value:%d\n", n.d64, n.id[1], n.id[0]);
}

#define HEAD(l) l.id[0]
#define TAIL(l) l.id[1]
union list_t {
   u64 d64;
   u32 id[2];
};

void list_init(union list_t* list)
{
   list->d64 = 0;
}

void list_print(union list_t list, union node_t* nodes)
{
   printf("list.d64:%016llX head:%08X tail:%08X\n", list.d64, list.id[0], list.id[1]);
   u32 next = HEAD(list);
   while(next) {
      union node_t n = nodes[next];
      node_print(n);
      next = n.id[1];
   }
}

void list_tail_append(union list_t *list, u32 nID, union node_t* nodes)
{
	if (list->d64 == 0) {
		list->id[0] = nID;
		list->id[1] = nID;
	} else {
		union node_t * tail = &nodes[list->id[1]];
		tail->id[1] = nID;
		list->id[1] = nID;
	}
}

void list_head_append(union list_t *list, u32 nID, union node_t* nodes)
{
	if (list->d64 == 0) {
		list->id[0] = nID;
		list->id[1] = nID;
	} else {
		union node_t * head = &nodes[nID];
		head->id[1] = list->id[0];
		list->id[0] = nID;
	}
}

int main(void) {
	union list_t list1, list2;
	union node_t arr1[4];
	union node_t arr2[4];
	list_init(&list1);
	list_init(&list2);

	for(int i=0; i< 4; i++) {
		VALUE(arr1[i]) = 100 + i;
		NEXT(arr1[i])  = 0;
		list_tail_append(&list1, i, arr1); 

		VALUE(arr2[i]) = 200 + i;
		NEXT(arr2[i]) = 0;
		list_head_append(&list2, i, arr2); 
	}	

	list_print(list1, arr1);
	list_print(list2, arr2);
	return 0;
}
