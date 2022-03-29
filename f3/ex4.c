#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define READ_ONLY 0
#define LOWERCASE 1
#define UPPERCASE 2

void print_usage(){
  printf("Usage: [-u | -l] [filename]\n");
}

void print_file(char *filename, int mode){
  FILE* f = fopen(filename, "r");
  if(f == NULL)
    printf("\n\t----- FILE NOT FOUND -----\n\n");

  while(!feof(f)){
    fread(c, sizeof(char), 1, f);
    
    if(mode == UPPERCASE)
      printf("%s", toupper(c));
    else if(mode == LOWERCASE)
      printf("%s", tolower(c));
    else
      printf("%s", c);
  }

  fclose(f);
}

void parse(int argc, char** argv){
  switch(argc){
    case 1:
      print_usage();
      break;

    case 2:
      print_file(argv[1], READ_ONLY)

    case 3:
      if(!strcmp(argv[1], "-u"))
        print_file(argv[1], UPPERCASE);
      else if(!strcmp(argv[1], "-v"))
        print_file(argv[1], LOWECASE);
      else
        print_usage();
  }
}

int main(int argc, char** argv){
  parse(argc, argv);
}