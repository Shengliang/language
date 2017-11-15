
// C program to multiply two square matrices
// http://www.geeksforgeeks.org/c-program-multiply-two-matrices/
#include<stdio.h>

// #define MS 10000
#define MS 100

int m1[MS][MS];
int m2[MS][MS];
int res[MS][MS];
 
void multiply(int m1[][MS], int m2[][MS])
{
    int x, i, j;
    for (i = 0; i < MS; i++) {
        for (j = 0; j < MS; j++) {
	    printf("SW %p\n", &res[i][j]);
            res[i][j] = 0;
            for (x = 0; x < MS; x++) {
		printf("LW %p\n", &m1[i][x]);
		printf("LW %p\n", &m2[x][j]);
		printf("LW %p\n", &res[i][j]);
		printf("SW %p\n", &res[i][j]);
                res[i][j] += m1[i][x] * m2[x][j];
            }
        }
    }
    for (i = 0; i < MS; i++) {
        for (j = 0; j < MS; j++) {
            printf("%d ", res[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
 
void init(int m[][MS])
{
  for(int i=0; i<MS; i++) {
    for(int j=0; j<MS; j++) {
        m[i][j] = i*MS +j; 
    }
  } 
}

int main()
{
    init(m1);
    init(m2);
    multiply(m1, m2);
    return 0;
}
