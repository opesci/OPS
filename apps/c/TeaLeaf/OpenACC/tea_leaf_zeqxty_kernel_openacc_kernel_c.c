//
// auto-generated by ops.py
//
#include "./OpenACC/tea_leaf_common.h"

#undef OPS_GPU

int xdim0_tea_leaf_zeqxty_kernel;
int xdim1_tea_leaf_zeqxty_kernel;
int xdim2_tea_leaf_zeqxty_kernel;


#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2


#define OPS_ACC0(x,y) (x+xdim0_tea_leaf_zeqxty_kernel*(y))
#define OPS_ACC1(x,y) (x+xdim1_tea_leaf_zeqxty_kernel*(y))
#define OPS_ACC2(x,y) (x+xdim2_tea_leaf_zeqxty_kernel*(y))

//user function
inline
void tea_leaf_zeqxty_kernel(double * z, const double * x, const double * y) {
  z[OPS_ACC0(0,0)] = x[OPS_ACC1(0,0)] * y[OPS_ACC2(0,0)];
}


#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2



void tea_leaf_zeqxty_kernel_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  int x_size, int y_size) {
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2)
  #pragma acc loop
  #endif
  for ( int n_y=0; n_y<y_size; n_y++ ){
    #ifdef OPS_GPU
    #pragma acc loop
    #endif
    for ( int n_x=0; n_x<x_size; n_x++ ){
      tea_leaf_zeqxty_kernel(  p_a0 + n_x*1*1 + n_y*xdim0_tea_leaf_zeqxty_kernel*1*1,
           p_a1 + n_x*1*1 + n_y*xdim1_tea_leaf_zeqxty_kernel*1*1, p_a2 + n_x*1*1 + n_y*xdim2_tea_leaf_zeqxty_kernel*1*1 );

    }
  }
}
