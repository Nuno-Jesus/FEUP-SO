#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix.h"

/* implementation of the matrix API */
matrix *matrix_new(int n, int m){
  matrix *u = (matrix *)malloc(sizeof(matrix));
  u->n = n;
  u->m = m;
  u->vals = (double *)malloc((u->n * u->m) * sizeof(double));

  for(int row = 0; row < u->n; row++){
    for(int col = 0; col < u->m; col++){
      matrix_set(row, col, 0.0, u);
    }
  }

  return u;
}

matrix *matrix_new_random(int n, int m, double min, double max){
  matrix *u = (matrix *)malloc(sizeof(matrix));
  u->n = n;
  u->m = m;
  u->vals = (double *)malloc((u->n * u->m) * sizeof(double));
  int i, j;
  double range = max - min;
  double div = RAND_MAX / range;
  for (i = 0; i < u->n; i++)
    for (j = 0; j < u->m; j++)
      matrix_set(i, j, min + (rand() / div), u);
  return u;
}

void matrix_print(matrix *u){
  printf("{ \n");
  for(int i = 0; i < u->m; i++){
    printf("   { ");
    for(int k = 0; k < u->n; k++){
      printf("%lf ", u->vals[i*u->m + k]);
    }

    printf("}\n");
  }
  printf("}\n\n");
}

double matrix_get(int row, int col, matrix *u){
  return *(u->vals + row * u->m + col);
}

void matrix_set(int row, int col, double val, matrix *u){
  u->vals[row * u->m + col] = val;
}

matrix *matrix_add(matrix *u, matrix *v){
  if(v == NULL || u == NULL || (u->m != v->m && u->n != v->n))
    return NULL;

  int i, j;
  matrix *w = matrix_new(u->n, u->m);
  for (i = 0; i < u->n; i++)
    for (j = 0; j < u->m; j++)
      matrix_set(i, j, matrix_get(i, j, u) + matrix_get(i, j, v), w);
  return w;
}

matrix *matrix_sub(matrix *u, matrix *v){
  if(v == NULL || u == NULL || (u->m != v->m && u->n != v->n))
    return NULL;
    
  int i, j;
  matrix *w = matrix_new(u->n, u->m);
  for (i = 0; i < u->n; i++)
    for (j = 0; j < u->m; j++)
      matrix_set(i, j, matrix_get(i, j, u) - matrix_get(i, j, v), w);
  return w;
}

matrix *matrix_mul(matrix *m1, matrix *m2){
  if(m1->m != m2->n || m1 == NULL || m2 == NULL)
    return NULL;

  //New matrix with the rows of the first and the columns of the second
  //m1 (M x N) / m2 (N x P) / m3 (M x P)
  matrix* mat = matrix_new(m1->n, m2->m);

  //For each row of the new matrix
  for(int row = 0; row < mat->n; row++){
    //For each column of the new matrix
    for(int col = 0; col < mat->m; col++){
      //For loop ranged to the common dimensions
      for(int k = 0; k < m1->m; k++){
        matrix_set(
          row, col, 
          matrix_get(row, col, mat) + matrix_get(row, k, m1) * matrix_get(k, col, m2),
          mat
        );
      }
    }
  }

  return mat;
}

matrix *matrix_trans(matrix *u){
  if(u == NULL || u->m != u->n)
    return NULL;
  
  matrix *m = matrix_new(u->n, u->m);
  
  for(int i = 0; i < u->n; i++){
    for(int j = 0; j < u->m; j++){
      m->vals[j*u->m + i] = u->vals[i*u->m + j];
    }
  }

  return m;
}