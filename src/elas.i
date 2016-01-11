%module elas

%{
#define SWIG_FILE_WITH_INIT
#include "elas.h"
%}

%feature("flatnested");
%feature("autodoc","0");

// handle numpy
%include numpy.i
%init %{
  import_array();
%}

%include "std_vector.i"
%include "std_string.i"

%rename (Elas_parameters) Elas::parameters;
%rename (ROBOTICS) Elas::ROBOTICS;
%rename (MIDDLEBURY) Elas::MIDDLEBURY;

%apply (unsigned char* IN_ARRAY2, int DIM1, int DIM2) { (unsigned char* image1, int rows1, int cols1),
     (unsigned char* image2, int rows2, int cols2)}
%apply (float* INPLACE_ARRAY2, int DIM1, int DIM2) { (float* disp1, int drows1, int dcols1),
     (float* disp2, int drows2, int dcols2)}

typedef int int32_t;
%include "elas.h"

%ignore Elas::process;
%extend Elas {
  void process_stereo(unsigned char* image1, int rows1, int cols1, 
		      unsigned char* image2, int rows2, int cols2,
		      float* disp1, int drows1, int dcols1,
		      float* disp2, int drows2, int dcols2) {
    int dims[] = {cols1, rows1, cols1};
    $self->process(image1, image2, disp1, disp2, dims);
  }
}
