#include <stdio.h>
#include <string.h>

#define CHARS 0
#define WORDS 1
#define LINES 2

void print_usage(){
  printf("Usage: command [-c | -w | -l] filename\n");
}

void readFile(char* filename, int mode){
  int numWords = 0, numChars = 0, numLines = 0;
  FILE* f = fopen(filename, "r");
  
  char* c;
  while(!feof(f)){
    fread(c, sizeof(1), 1, f);
    if()
  }
}

void parse(int argc, char** argv){
  if(!strcmp(argv[1], "-c") || argc == 2)
    readFile(argv[2], CHARS);

  else if(!strcmp(argv[1], "-w"))
    readFile(argv[2], WORDS);

  else if(!strcmp(argv[1], "-l"))
    readFile(argv[2], LINES);

  else
    print_usage();
}

int main(int argc, char** argv){
  if(argc < 2 || argc > 3)
    print_usage();

  parse(argc, argv);
}