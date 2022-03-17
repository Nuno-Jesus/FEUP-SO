typedef struct{
  double x;
  double y;
  double z;
} vector;

vector* vector_new(double x, double y, double z);
vector* vector_add(vector* a, vector* b);
vector* vector_sub(vector* a, vector* b);
vector* vector_scale(double s, vector* a);
vector* vector_vprod(vector* a, vector* b);
double vector_sprod(vector* a, vector* b);
double vector_mod(vector* a);