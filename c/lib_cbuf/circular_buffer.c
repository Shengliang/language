
#include "circular_buffer.h" 

void CircularBufferInit(CircularBuffer* cbuf)
{
	int i;
        cbuf->size = MAX_BUFFER_SIZE;
        cbuf->mask = BUFFER_POINTER_MASK;
        cbuf->writePointer = 0;
        cbuf->readPointer  = 0;
	for (i = 0; i < MAX_BUFFER_SIZE; ++i) {
		cbuf->data[i] = 0;
	}	
}
 
int CircularBufferIsFull(CircularBuffer* cbuf)
{
     return (((cbuf->writePointer + 1) & cbuf->mask) == cbuf->readPointer); 
}
 
int CircularBufferIsEmpty(CircularBuffer* cbuf)
{
     return (cbuf->readPointer == cbuf->writePointer); 
}
 
int CircularBufferEnque(CircularBuffer* cbuf, DataType k)
{
        int isFull = CircularBufferIsFull(cbuf);
        if(!isFull) {
        	cbuf->data[cbuf->writePointer] = k;
        	cbuf->writePointer++;
        	cbuf->writePointer &= cbuf->mask;
        }
        return isFull;
}
 
int CircularBufferDeque(CircularBuffer* cbuf, DataType* pK)
{
        int isEmpty =  CircularBufferIsEmpty(cbuf);
        if(!isEmpty) {
	        *pK = cbuf->data[cbuf->readPointer];
	        cbuf->readPointer++;
	        cbuf->readPointer &= cbuf->mask;
        }
        return(isEmpty);
}
 
