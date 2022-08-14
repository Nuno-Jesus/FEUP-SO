#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 256

void copyFile(char* src, char* dst){
  FILE* source = fopen(src, "r");
  if(source == NULL){
    printf("\n\t----- SOURCE FILE NOT FOUND -----\n\n");
    return;
  }

  FILE* destination = fopen(dst, "w");
  if(destination == NULL){
    printf("\n\t----- DESTINATION FILE NOT FOUND -----\n\n");
    return;
  }

  char block[BLOCK_SIZE];
  size_t size = 0;
  int stop = 0;
  
  while(!stop){
    if((size = fread(block, BLOCK_SIZE, 1, source)) < BLOCK_SIZE)
      stop = 1;

    fwrite(block, strlen(block), 1, destination);
  }

  fclose(source);
  fclose(destination);
}

void print_usage(){
  printf("Usage: command file_src file_dst\n");
}

int main(int argc, char** argv){
  if(argc < 3){
    print_usage();
    return -1;
  }

  copyFile(argv[1], argv[2]);
  return 0;
}