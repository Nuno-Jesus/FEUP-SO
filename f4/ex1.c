#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int next_block_size(int count, int buffer_size){
  return (count >= buffer_size) ? buffer_size : count % buffer_size;
}

void print_file(int fd, struct stat info){
  int count = info.st_size;
  char buffer[BUFFER_SIZE];
  while (count != 0){
    int bytesin = read(fd, buffer, next_block_size(count, BUFFER_SIZE));
    count -= bytesin;
    write(STDOUT_FILENO, buffer, bytesin);
  }
}

int open_file(char* filename){
  int fd = open(filename, O_RDONLY);
  if (fd == -1){
    printf("error: cannot open %s\n", filename);
    exit(-1);
  }

  return fd;
}

struct stat read_status(char* filename){
  struct stat info;
  
  if (lstat(filename, &info) == -1){
    printf("error: cannot stat %s\n", filename);
    exit(-1);
  }

  return info;
}

int main(int argc, char *argv[]){
  /* check if exactly one argument is present */
  if (argc < 2){
    printf("usage: cat [filename]+\n");
    return EXIT_FAILURE;
  }

  for(int i = 1; i < argc; i++){
    /* check if the file exists and is can be read */
    int fd = open_file(argv[i]);
    
    /* get the file size */
    struct stat info = read_status(argv[i]);
    
    /* print the contents in blocks */
    print_file(fd, info);
    
    /* close file */
    close(fd);

    printf("\n");
  }

  


  
  
  return EXIT_SUCCESS;
}