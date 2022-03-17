#include "matrix.h"

int main(){
  matrix* m1 = matrix_new_random(4, 3, 1.0, 10.0);
  matrix* m2 = matrix_new_random(3, 4, 1.0, 10.0);
  matrix* m3 = matrix_add(m1, m2);
  matrix* m4 = matrix_sub(m1, m2);
  matrix* m5 = matrix_mul(m1, m2);
  matrix* m6 = matrix_trans(m1);

  matrix_print(m1);
}