#include "matrix.h"
#include <stdio.h>

int main(){
  matrix* m1 = matrix_new_random(2, 2, 1.0, 2.0);
  matrix* m2 = matrix_new_random(2, 2, 1.0, 2.0);
  matrix* m3 = matrix_add(m1, m2);
  matrix* m4 = matrix_sub(m1, m2);
  matrix* m5 = matrix_mul(m1, m2);
  matrix* m6 = matrix_trans(m1);

  printf("m1\n");
  matrix_print(m1);

  printf("m2\n");
  matrix_print(m2);

 /*  printf("m3\n");
  matrix_print(m3);

  printf("m4\n");
  matrix_print(m4); */

  printf("m5\n");
  matrix_print(m5);

 /*  printf("m6\n");
  matrix_print(m6); */

  return 0;
}