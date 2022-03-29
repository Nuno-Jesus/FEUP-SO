#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define READ_ONLY 0
#define LOWERCASE 1
#define UPPERCASE 2
#define BLOCK_USAGE 255

void tolowerString(char* target){
  for(int i = 0; i < strlen(target); i++)
    if(target[i] >= 'A' && target[i] <= 'Z')
      target[i] = tolower(target[i]);
}

void toupperString(char* target){
  for(int i = 0; i < strlen(target); i++)
    if(target[i] >= 'a' && target[i] <= 'z')
      target[i] = toupper(target[i]);
}

void print_usage(){
  printf("Usage: [-u | -l] [filename]\n");
}

void print_file(char *filename, int mode){
  char block[BLOCK_USAGE];
  int stop = 0;
  size_t size = 0;

  FILE* f = fopen(filename, "r");
  if(f == NULL){
    printf("\n\t----- FILE NOT FOUND -----\n\n");
    return;
  }

  while(!stop){
    if((size = fread(block, BLOCK_USAGE, 1, f)) < BLOCK_USAGE)
      stop = 1;
    
    if(mode == UPPERCASE)
      toupperString(block);
    else if(mode == LOWERCASE)
      tolowerString(block);

    puts(block);
  }

  fclose(f);
}

void parse(int argc, char** argv){
  switch(argc){
    case 1:
      print_usage();
      break;

    case 2:
      print_file(argv[1], READ_ONLY);

    case 3:
      if(!strcmp(argv[1], "-u"))
        print_file(argv[2], UPPERCASE);
      else if(!strcmp(argv[1], "-l"))
        print_file(argv[2], LOWERCASE);
      else
        print_usage();
  }
}

int main(int argc, char** argv){
  parse(argc, argv);
}