//
// auto-generated by ops.py
//
#include "./OpenACC/tea_leaf_common.h"

#undef OPS_GPU

int xdim0_tea_leaf_cg_calc_ur_r_reduce_kernel;
int xdim1_tea_leaf_cg_calc_ur_r_reduce_kernel;


#undef OPS_ACC0
#undef OPS_ACC1


#define OPS_ACC0(x,y) (x+xdim0_tea_leaf_cg_calc_ur_r_reduce_kernel*(y))
#define OPS_ACC1(x,y) (x+xdim1_tea_leaf_cg_calc_ur_r_reduce_kernel*(y))

//user function
inline
void tea_leaf_cg_calc_ur_r_reduce_kernel(double * r, const double * w, const double * alpha, double *rnn) {
  r[OPS_ACC0(0,0)] = r[OPS_ACC0(0,0)] - (*alpha)*w[OPS_ACC1(0,0)];
  *rnn = *rnn +  r[OPS_ACC0(0,0)]*r[OPS_ACC0(0,0)];
}


#undef OPS_ACC0
#undef OPS_ACC1



void tea_leaf_cg_calc_ur_r_reduce_kernel_c_wrapper(
  double *p_a0,
  double *p_a1,
  double p_a2,
  double *p_a3,
  int x_size, int y_size) {
  double p_a3_0 = p_a3[0];
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1) reduction(+:p_a3_0)
  #pragma acc loop reduction(+:p_a3_0)
  #endif
  for ( int n_y=0; n_y<y_size; n_y++ ){
    #ifdef OPS_GPU
    #pragma acc loop reduction(+:p_a3_0)
    #endif
    for ( int n_x=0; n_x<x_size; n_x++ ){
      tea_leaf_cg_calc_ur_r_reduce_kernel(  p_a0 + n_x*1*1 + n_y*xdim0_tea_leaf_cg_calc_ur_r_reduce_kernel*1*1,
           p_a1 + n_x*1*1 + n_y*xdim1_tea_leaf_cg_calc_ur_r_reduce_kernel*1*1, &p_a2,
           &p_a3_0 );

    }
  }
  p_a3[0] = p_a3_0;
}
