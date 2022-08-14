#include "vector.h"
#include <math.h>
#include <stdlib.h>

vector* vector_new(double x, double y, double z){
  vector* v = (vector*) malloc(sizeof(vector));
  if(v == NULL)
    return NULL;

  v->x = x;
  v->y = y;
  v->z = z;

  return v;
}

vector* vector_add(vector* a, vector* b){
  return vector_new(a->x + b->x, a->y + b->y, a->z + b->z);
}

vector* vector_sub(vector* a, vector* b){
  return vector_new(a->x - b->x, a->y - b->y, a->z - b->z);
}

vector* vector_scale(double s, vector* a){
  return vector_new(s * a->x, s * a->y, s* a->z);
}

vector* vector_vprod(vector* a, vector* b){
  return vector_new(a->y * b->z - a->z * b->y, a->z * b->x - a->x * b->z, a->x * b->y - a->y * b->x);
}

double vector_sprod(vector* a, vector* b){
  return a->x * b->x + a->y * b->y + a->z * b->z;
}

double vector_mod(vector* a){
  return sqrt(pow(a->x, 2) + pow(a->y, 2) + pow(a->z, 2));
}

