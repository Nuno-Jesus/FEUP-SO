#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SIZE 1024

int main(int argc, char** argv){
  char path[SIZE];
  if(!getcwd(path, SIZE)){
    fprintf(stderr, "\n\t----- THE CURRENT PATH IS TOO BIG -----\n\n");
    return EXIT_FAILURE;
  }

  puts(path);
  return EXIT_SUCCESS;
}