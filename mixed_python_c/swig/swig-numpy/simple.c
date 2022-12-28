#include "simple.h"

double dot(int n, double *a, int m, double *b) {
  int i;

  double sum = 0.0;
  for (i = 0; i < n; i++) {
    sum += a[i] * b[i];
  }
  return sum;
}

void arange(int size, double *arr) {
  int i;

  for (i = 0; i < size; i++)
    arr[i] = i;
}

// get/set-------------------------
double foo = 3.4;
double get_foo() {
  return foo;
}

void set_foo(double x) {
  foo = x;
}
// ---------------------------------

// typedefs and structs
void function_custom_struct(custom_struct cs) {
  cs1 = cs;
}