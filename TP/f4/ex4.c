#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <utime.h>

void print_usage(){
  printf("Usage: command filename\n");
  exit(-1);
}

void create_file(char* filename){
  //Creates the file
  if(open(filename, O_CREAT) == -1){
    fprintf(stderr, "\n\t----- COULDN'T CREATE THE %s FILE -----\n\n", filename);
    exit(-1);
  }

  //Sets up new perms
  mode_t perms = 0;
  perms |= S_IRUSR | S_IXUSR | S_IRGRP | S_IROTH; //644
  if(chmod(filename, perms) == -1){
    fprintf(stderr, "\n\t----- COULDN'T SET THE PERMISSIONS OF %s -----\n\n", filename);
    exit(-1);
  }

  printf("The file %s was created successfully.\n", filename);
}

void change_access_time(char* filename){
  int fd = open(filename, O_RDONLY);
  if(fd == -1){
    fprintf(stderr, "\n\t----- THE FILE %s COULDN'T BE OPENED -----\n\n", filename);
    exit(-1);
  }

  //The call to utime changes the access and modifying dates according to what exists in buffer
  struct utimbuf buffer;
  buffer.actime = time(NULL);
  utime(filename, &buffer);

  printf("Successfully changed the access date of %s to today.\n", filename);
}

int main(int argc, char**argv){
  if(argc != 2)
    print_usage();

  //Checks if the file
  int fd = open(argv[1], O_RDONLY);
  if(fd == -1)
    create_file(argv[1]);
  else
    change_access_time(argv[1]);

  return 0;
}