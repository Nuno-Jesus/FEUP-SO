#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

void print_usage(char* command){
  printf("Usage: %s filename\n", command);
  exit(-1);
}

void print_permissions(mode_t permissions){
  printf("-");
  /* User permissions */
  if(permissions & S_IRUSR) printf("r"); else printf("-");
  if(permissions & S_IWUSR) printf("w"); else printf("-");
  if(permissions & S_IXUSR) printf("x"); else printf("-");

  /* Group permissions */
  if(permissions & S_IRGRP) printf("r"); else printf("-");
  if(permissions & S_IWGRP) printf("w"); else printf("-");
  if(permissions & S_IXGRP) printf("x"); else printf("-");

  /* Other permissions */
  if(permissions & S_IROTH) printf("r"); else printf("-");
  if(permissions & S_IWOTH) printf("w"); else printf("-");
  if(permissions & S_IXOTH) printf("x"); else printf("-");
  printf(" ");
}

void list_directory(char* filename){
  struct dirent *p;
  DIR *q;

  q = opendir(filename);
  if (q == NULL){
    fprintf(stderr, "\n\t----- CANNOT OPEN DIRECTORY '%s' -----\n\n",filename);
    exit(-1);
  }
    
  printf("%s/\n", filename);
  p = readdir(q);
  while (p != NULL){
    printf("\t%s\n", p->d_name);
    p = readdir(q);
  }

  closedir(q);
}

void list_file(char* filename){
  struct stat info = read_status(filename);
  print_permissions(info.st_mode);
}

struct stat read_status(char* filename){
  struct stat info;
  if(lstat(filename, &info) == -1){
    fprintf(stderr, "\n\t----- COULDN'T READ %s STATUS -----\n\n", filename);
    exit(-1);
  }

  return info;
}

int main(int argc, char **argv){
  if(argc != 2)
    print_usage(argv[0]);

  /* Reads the file status */  
  struct stat info = read_status(argv[1]);
  
  /* If the file is a directory */
  if(S_ISDIR(info.st_mode))
    list_directory(argv[1]);
  else
    list_file(argv[1], info);

  return EXIT_SUCCESS;
}