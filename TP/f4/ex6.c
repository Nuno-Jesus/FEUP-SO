#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <sys/stat.h>

#define GREEN   "\x1b[32m"
#define BACK_GREEN   "\x1b[42m"
#define BACK_BLACK   "\x1b[40m"
#define RESET "\x1b[0m"

void print_permissions(mode_t permissions, bool isDirectory);
void print_ownership(uid_t uid, gid_t gid);
void print_modification_date(struct timespec date);
void print_size(int size);
struct stat read_status(char* filename);
void list_file(char* filename);
void list_directory(char* filename);


void print_usage(char* command){
  printf("Usage: %s filename\n", command);
  exit(-1);
}

void print_permissions(mode_t permissions, bool isDirectory){
  isDirectory ? printf("d") : printf("-");

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

void print_links(int links){
  printf("%d ", links);
}

void print_ownership(uid_t uid, gid_t gid){
  struct passwd* user_info = getpwuid(uid);
  struct group* group_info = getgrgid(uid);

  if(user_info != NULL && group_info != NULL)
    printf("%s %s ", user_info->pw_name, group_info->gr_name);
}

void print_modification_date(struct timespec date){
  char* buffer = ctime(&date.tv_sec);
  buffer[strlen(buffer) - 1] = '\0';
  printf("%s ", buffer);
}

void print_size(int size){
  printf("%3d ", size);
}

void print_filename(char* filename, bool isDirectory){
  isDirectory ? printf(GREEN "%s \n" RESET, filename) : printf(GREEN "%s \n" RESET, filename);
}

struct stat read_status(char* filename){
  struct stat info;
  if(lstat(filename, &info) == -1){
    fprintf(stderr, "\n\t----- COULDN'T READ %s STATUS -----\n\n", filename);
    exit(-1);
  }

  return info;
}

void list_file(char* filename){
  struct stat info = read_status(filename);
  
  print_permissions(info.st_mode, S_ISDIR(info.st_mode));
  print_links((int)info.st_nlink);
  print_ownership(info.st_uid, info.st_gid);
  print_size((int)info.st_size);
  print_modification_date(info.st_mtim);
  print_filename(filename, S_ISDIR(info.st_mode));
}

void list_directory(char* filename){
  struct dirent *p;
  DIR *q;

  q = opendir(filename);
  if (q == NULL){
    fprintf(stderr, "\n\t----- CANNOT OPEN DIRECTORY '%s' -----\n\n",filename);
    exit(-1);
  }
    
  printf("%s:\n", filename);
  p = readdir(q);
  while (p != NULL){
    list_file(p->d_name);
    p = readdir(q);
  }

  closedir(q);
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
    list_file(argv[1]);

  return EXIT_SUCCESS;
}