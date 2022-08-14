#include <stdio.h>

#define BLOCK_SIZE 256

void printFile(char* file){
  char block[BLOCK_SIZE];
  size_t size;
  FILE* f = fopen(file, "r");
  
  if(f == NULL){
    printf("\n\t----- FILE NOT FOUND -----\n\n");
    return;
  }

  int stop = 0;
  while(!stop){
    if((size = fread(block, BLOCK_SIZE, 1, f)) < BLOCK_SIZE)
      stop = 1;

    puts(block);
  }
}

void printFiles(int n, char** files){
  for(int i = 0; i < n; i++)
    printFile(files[i + 1]);
}

int main(int argc, char** argv){
  if(argc < 2){
    printf("Usage: [filename]+");
    return -1;
  }

  printFiles(argc - 1, argv);
}