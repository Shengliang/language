#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__
 
/*!
 * Circular Buffer: Implementation based on: Keep one slot open
 */

/* For fast performance, the size must be power of 2. */ 
#define MAX_BUFFER_SIZE  64 
#define BUFFER_POINTER_MASK  (MAX_BUFFER_SIZE-1)
#define MAX_NUM_OF_ELEMS     (MAX_BUFFER_SIZE-1)
 
/**< Circular Buffer Types */
typedef unsigned char uint8;
typedef uint8 DataType;

typedef struct
{
   uint8 writePointer; /**< write pointer */
   uint8 readPointer;  /**< read pointer */
   uint8 size;         /**< size of circular buffer */
   uint8 mask;         /**< bit Mask of circular buffer size*/
   DataType data[MAX_BUFFER_SIZE];    /**< Element of ciruclar buffer */
} CircularBuffer;
 
void CircularBufferInit(CircularBuffer* cbuf);
int CircularBufferIsFull(CircularBuffer* cbuf);
int CircularBufferIsEmpty(CircularBuffer* cbuf);
int CircularBufferEnque(CircularBuffer* cbuf, DataType data);
int CircularBufferDeque(CircularBuffer* cbuf, DataType* pdata);
 
#endif
