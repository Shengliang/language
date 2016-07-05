/* ref:
 * http://www.geeksforgeeks.org/write-a-c-program-that-doesnt-terminate-when-ctrlc-is-pressed/
 */

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<signal.h>

/*
SIGABRT – abnormal termination.
SIGFPE – floating point exception.
SIGILL – invalid instruction.
SIGINT – interactive attention request sent to the program.
SIGSEGV – invalid memory access.
SIGTERM – termination request sent to the program.
*/

static volatile int g_counter = 0;
static volatile int g_signum = 0;
void initHandler(int signum)
{
   g_counter++;
   g_signum = signum;
}

int main(int argc, char* argv[])
{
  int loop = -1, i=0;
  if (argc>1) 
    loop = atoi(argv[1]);
  signal(SIGINT, initHandler);
  while (loop == -1 || (i < loop)) {
    printf("%d:%d:%d\n", i++, g_signum, g_counter);
    sleep(1);
  }
  return 0;
}
