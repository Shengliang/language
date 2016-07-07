// ref: http://www.geeksforgeeks.org/multithreading-c-2/
// gcc  multithreading.c -lpthread
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 
// Let us create a global variable to change it in threads
#define MAX_NUM_OF_THREADS 3
int g_ids[MAX_NUM_OF_THREADS];
int g = 0;
 
// The function to be executed by all threads
void *myThreadFun(void *vargp)
{
    // Store the value argument passed to this thread
    int myid = *((int*)vargp);
 
    // Let us create a static variable to observe its changes
    static int s = 0;
 
    // Change static and global variables
    ++s; ++g;
 
    // Print the argument, static and global variables
    printf("Thread ID: %d, Static: %d, Global: %d\n", myid, ++s, ++g);
}
 
int main()
{
    int i;
    pthread_t tid;
 
    // Let us create three threads
    for (i = 0; i < MAX_NUM_OF_THREADS; i++) {
	g_ids[i] = 42 + i;
        pthread_create(&tid, NULL, myThreadFun, (void *)&g_ids[i]);
    }
    pthread_exit(NULL);
    return 0; 
}
