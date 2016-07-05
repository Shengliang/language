#include<stdlib.h>
#include<time.h>
#include<stdio.h>

int get(void)
{
int r = rand() & 0xF;
while (r < 1 || r > 11) {
  r = rand() & 0xF;
}
  return r;
}
void main(void)
{
  int i;
  srand(time(NULL));
  for(i=0; i<16; i++)
    printf("%d\n", get());
}

