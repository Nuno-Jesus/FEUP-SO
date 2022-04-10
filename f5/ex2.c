#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * !Q2: How many processes are created?
 * Since every iteration 2 new processes are created, 2^4 = 16 
*/

int main(int argc, char *argv[]){
  for (int i = 0; i < 4; i++)
    fork();

  printf("PID: %d\n", getpid());
  return EXIT_SUCCESS;
}