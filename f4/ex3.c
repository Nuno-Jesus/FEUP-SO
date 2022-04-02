#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

struct stat read_status(char* filename){
  struct stat info;
  if(lstat(filename, &info) == -1){
    fprintf(stderr, "fsize: Can't stat %s\n", filename);
    exit(-1);
  }

  return info;
}

void print_status(char* filename, struct stat info){
  printf("%s:\n", filename);
  printf(" > Size: %d bytes,  %d\n", (int)info.st_size);
  printf(" > Disk Blocks: %d bytes,  %d\n", (int)info.st_blocks);
  printf(" > Date of the last modification: %d\n", (int)info.st_atime);
  printf(" > Owner of the file: %d\n", (int)info.st_uid);
  printf("\n");
}

int main(int argc, char *argv[]){
  if(argc < 2){
    fprintf(stderr, "usage: %s file\n", argv[0]);
    return EXIT_FAILURE;
  }

  for(int i = 1; i < argc; i++){
    struct stat info = read_status(argv[i]);
    print_status(argv[i], info);
  }

  return EXIT_SUCCESS;
}
