#include <stdio.h>
#include <string.h>

int isSubstring(char *needle, char* haystack){
  return strstr(haystack, needle) != NULL ? 1 : 0; 
}

int main(int argc, char **argv){
  if(argc != 3){
    printf("Usage: command needle haystack\n");
    return -1;
  }

  if(isSubstring(argv[1], argv[2]))
    printf("The first string occurs in the second\n");

  else
    printf("The first string does not occur in the second\n");
  
  return 0;
}