#include <stdio.h>
#include "circular_buffer.h" 

int CircularBufferPrint(CircularBuffer* cbuf)
{
        int i=0;
        int isEmpty =  CircularBufferIsEmpty(cbuf);
        int isFull  =  CircularBufferIsFull(cbuf);
        printf("\n==Q: w:%d r:%d f:%d e:%d\n", 
            cbuf->writePointer, cbuf->readPointer,  isFull, isEmpty);
        for(i=0; i< cbuf->size; i++) {
           printf("%d ", cbuf->data[i]);
        }
        printf("\n");
        return(isEmpty);
}
 
int main(int argc, char *argv[])
{
        CircularBuffer cbuf;
        DataType first = 1;
        DataType last  = first + MAX_NUM_OF_ELEMS - 1;
	DataType num;
        int isEmpty, i;
 
        CircularBufferInit(&cbuf);
 
        printf("Test: Insert %d-%d\n", first, last);
	num = first;
        while(!CircularBufferEnque(&cbuf, num++));
 
	int sum = 0;
        do {
            num = 0;
            isEmpty = CircularBufferDeque(&cbuf, &num); 
	    sum += num;
        } while (!isEmpty);

        CircularBufferPrint(&cbuf);
	sum -= ((first+last)*(MAX_NUM_OF_ELEMS) >> 1);
	if (sum == 0) {
		printf("Passed.\n");
	} else {
		printf("Failed.\n");
	}
        return sum;
}
