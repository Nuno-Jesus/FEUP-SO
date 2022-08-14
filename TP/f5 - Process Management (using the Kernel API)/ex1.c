#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * !Q1: How many processes are created?
 * Fork is called 3 times, so 2^3 = 8 processes
*/

int main(int argc, char *argv[]){
  /* fork a child process */
  fork();

  /* fork another child process */
  fork();
  /* and fork another */
  fork();
  
  printf("PID: %d\n", getpid());
  return EXIT_SUCCESS;
}
