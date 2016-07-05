#include<stdio.h>

void print(char* m, int x, int y) {
  int n = (x > y) ? x : y;
  int lines = x + y - 1;
  for(int i = 0; i < lines; ++i) {
    for(int xi = i; xi >= 0; --xi) {
       if (xi > x) {
          xi = x - 1;
       }
       int yi = i - xi;
       if ((xi <  x) && (yi < y)) {
         printf("%c", *(m + xi*y + yi));
       }
    }
    printf("\n");
  } 
}

int main(void)
{
  char m[4][3] = { 
     {'a', 'b', 'c' },
     {'d', 'e', 'f' },
     {'g', 'h', 'i' },
     {'1', '2', '3' }  
 };
 for(int r = 0; r < 4; r++) {
   for(int c = 0; c < 3; c++) {
     printf("%c", m[r][c]);
   }
   printf("\n");
 }
 printf("Print m diagonally:\n");
 print((char*)m, 4, 3);
}
