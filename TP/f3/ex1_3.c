#include <stdio.h>
#include <string.h>

int countOccurences(char *needle, char* haystack){
  if(haystack == NULL || needle == NULL)
    return -1;

  int count = 0;

  //Replaces the auxiliar haystack pointer with the pointer of the newest occurence
  do{
    if((haystack = strstr(haystack, needle)) != NULL){
      count++;
      haystack++;
    }
  }while(haystack != NULL);

  return count;
}

int main(int argc, char **argv){
  if(argc != 3){
    printf("Usage: command needle haystack");
    return -1;
  }

  printf("Occurences: %d\n", countOccurences(argv[1], argv[2]));
  
  return 0;
}