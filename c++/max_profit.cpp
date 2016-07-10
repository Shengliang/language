
#include<stdio.h>

#ifdef __cplusplus
#include <limits>
#define INT_MAX std::numeric_limits<int>::max()
extern "C" {
#else
#include<limit.h>
#endif

void max_profit(const int num[], int size)
{
   int curr_min = INT_MAX;
   int curr_profit = 0 ;
   int pos = 0;
   for(int i = 0; i< size; i++) {
       if (curr_min > num[i]) {
          curr_min= num[i];
       }
       int p = num[i] - curr_min;
       if (p > curr_profit) {
           curr_profit = p;
           pos = i;
       }
   }
   printf("%d %d\n", curr_min, num[pos]);
}

#ifdef __cplusplus
}
#endif

int main(void)
{
   int arr[] = { 9, 1, 8, 2, 7, 3, 6, 4, 5, 11 }; 
   max_profit(arr, sizeof(arr)/sizeof(arr[0]));
   return 0;
}
