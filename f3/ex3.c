#include <stdio.h>

void printFile(char* file){
  char* c;
  FILE* f = fopen(file, "r");
  
  if(f == NULL){
    printf("\n\t----- FILE NOT FOUND -----\n\n");
    return;
  }

  while(!feof(f)){
    fread(c, sizeof(char), 1, f);
    printf("%s", c);
  }
}

void printFiles(char** files, int n){
  for(int i = 0; i < n; i++)
    printFile(files[i]);
}

int main(int argc, char** argv){
  if(argc < 2){
    printf("Usage: [filename]+");
    return -1;
  }

  printFiles(argv, n - 1);
}