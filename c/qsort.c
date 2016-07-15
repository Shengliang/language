#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct
{
   char name[32];
   int  age;
} Person;

int cmp (const void * a, const void * b)
{
   Person* pa = (Person*) a;
   Person* pb = (Person*) b;
   if (pa->age == pb->age)
      return strcmp(pa->name, pb->name);
   else
      return pa->age - pb->age;
}

int main() {
    Person arr[] = { 
     {"Alice", 14},
     {"Bob", 13},
     {"David", 14},
     {"Ella", 6}
    };
    int num = sizeof(arr)/sizeof(arr[0]);
    qsort(&arr[0], num, sizeof(arr[0]), cmp);
    for(int i=0; i<num; i++) {
       Person *p = &arr[i];
       printf("%d %s\n", p->age, p->name);
    }
    printf("\n");
    return 0;
}

