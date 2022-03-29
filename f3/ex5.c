#include <stdio.h>
#include <string.h>

void copyFile(char* src, char* dst){
  FILE* source = fopen(src, "r");
  if(source == NULL){
    printf("\n\t----- SOURCE FILE NOT FOUND -----\n\n");
    return;
  }

  FILE* destiny = fopen(dst, "r");
  if(destiny == NULL){
    printf("\n\t----- ERROR OPENING DESTINY FILE -----\n\n");
    return;
  }

  char* c;
  while(!feof(source)){
    fread(c, sizeof(char), 1, source);
    fwrite(c, sizeof(1), 1, destiny);
  }

  fclose(source);
  fclose(destiny);
}

void print_usage(){
  printf("Usage: command file_src file_dst\n");
}

int main(int argc, char** argv){
  if(argc < 3){
    print_usage();
    return;
  }

  copyFile(argv[1], argv[2]);
}