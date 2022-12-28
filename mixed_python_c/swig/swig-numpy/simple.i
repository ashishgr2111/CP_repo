%module simple
%{
 #define SWIG_FILE_WITH_INIT
 #include "simple.h"
%}

%include "numpy.i"
%init %{
import_array();
%}

// trying versions----------
#define VERSION "1.1"
%inline %{
  extern double foo;
  enum boolean {NO=0, YES=1};
%}
//--------------------------

// trying file apis----------
FILE *fopen(char *, char *);
int fclose(FILE *);
unsigned fread(void *ptr, unsigned size, unsigned nobj, FILE *);
unsigned fwrite(void *ptr, unsigned size, unsigned nobj, FILE *);
void *malloc(int nbytes);
void free(void *);
//--------------------------

%apply (int DIM1, double* IN_ARRAY1) {(int n, double *a), (int m, double *b)};
%apply (int DIM1, double* ARGOUT_ARRAY1) {(int size, double *arr)};
%include "simple.h"

%extend custom_struct {             // Attach these functions to struct custom_struct
  custom_struct(double x) {
    custom_struct *cs;
    cs = (custom_struct *) malloc(sizeof(custom_struct));
    cs->x = x;
    return cs;
  }
  ~custom_struct() {
    free($self);
  }
  double magnitude() {
    return sqrt($self->x*$self->x);
  }
  void _print() {
    printf("custom_struct [%f]\n", $self->x);
  }
};