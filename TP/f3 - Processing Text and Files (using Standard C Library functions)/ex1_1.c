#include <stdio.h>
#include <string.h>

void lowercase(char *string){
  for(int i = 0; i < strlen(string); i++)
    if(string[i] >= 'A' && string[i] <= 'Z')
      string[i] = string[i] - ('A' - 'a');
}

int main(int argc, char **argv){
  if(argc != 2){
    printf("Usage: command string");
    return -1;
  }

  printf("Argv1: %s\n", argv[1]);
  lowercase(argv[1]);
  printf("Argv1: %s\n", argv[1]);
  
  return 0;
}