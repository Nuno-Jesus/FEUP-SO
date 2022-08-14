#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
  printf(" > Date of the last modification: %s", ctime(&info.st_atime));
  printf(" > Owner of the file: UID = %d GID = %d\n", (int)info.st_uid, (int)info.st_gid);
  printf("\n");
}

int main(int argc, char *argv[]){
  if(argc < 2){
    fprintf(stderr, "usage: %s file\n", argv[0]);
    return EXIT_FAILURE;
  }

  int size = 0;
  int blocks = 0;

  for(int i = 1; i < argc; i++){
    struct stat info = read_status(argv[i]);
    print_status(argv[i], info);
    size += (int)info.st_size;
    blocks += (int)info.st_blksize;
  }

  printf("Total size of the files: %d\n", size);
  printf("Total blocks occupied: %d\n", blocks);

  return EXIT_SUCCESS;
}
