#include <stdio.h>

int main(){
  int i = 0, j = 0, *p = NULL, *q = NULL;
  
  i = 5;
  printf("i=%d, j=%d, p=%p, q=%p\n", i, j, p, q);

  p = &i;
  printf("i=%d, j=%d, p=%p, q=%p\n", i, j, p, q);

  *p = 7;
  printf("i=%d, j=%d, p=%p, q=%p\n", i, j, p, q);

  j = 3;
  printf("i=%d, j=%d, p=%p, q=%p\n", i, j, p, q);

  p = &j;
  printf("i=%d, j=%d, p=%p, q=%p\n", i, j, p, q);

  q = p;
  printf("i=%d, j=%d, p=%p, q=%p\n", i, j, p, q);

  p = &i;
  printf("i=%d, j=%d, p=%p, q=%p\n", i, j, p, q);

  *q = 2;
  printf("i=%d, j=%d, p=%p, q=%p\n", i, j, p, q);
  
  return 0;
}