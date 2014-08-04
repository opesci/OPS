//
// auto-generated by ops.py on 2014-07-31 11:59
//

#include "./OpenACC/clover_leaf_common.h"

int xdim0_calc_dt_kernel_print;
int xdim1_calc_dt_kernel_print;
int xdim2_calc_dt_kernel_print;
int xdim3_calc_dt_kernel_print;
int xdim4_calc_dt_kernel_print;
int xdim5_calc_dt_kernel_print;

#define OPS_ACC0(x,y) (x+xdim0_calc_dt_kernel_print*(y))
#define OPS_ACC1(x,y) (x+xdim1_calc_dt_kernel_print*(y))
#define OPS_ACC2(x,y) (x+xdim2_calc_dt_kernel_print*(y))
#define OPS_ACC3(x,y) (x+xdim3_calc_dt_kernel_print*(y))
#define OPS_ACC4(x,y) (x+xdim4_calc_dt_kernel_print*(y))
#define OPS_ACC5(x,y) (x+xdim5_calc_dt_kernel_print*(y))

//user function
inline 
void calc_dt_kernel_print(const double *xvel0, const double *yvel0,
                        const double *density0, const double *energy0,
                        const double *pressure, const double *soundspeed, double *output) {
  output[0] = xvel0[OPS_ACC0(1,0)];
  output[1] = yvel0[OPS_ACC1(1,0)];
  output[2] = xvel0[OPS_ACC0(-1,0)];
  output[3] = yvel0[OPS_ACC1(-1,0)];
  output[4] = xvel0[OPS_ACC0(0,1)];
  output[5] = yvel0[OPS_ACC1(0,1)];
  output[6] = xvel0[OPS_ACC0(0,-1)];
  output[7] = yvel0[OPS_ACC1(0,-1)];
  output[8] = density0[OPS_ACC2(0,0)];
  output[9] = energy0[OPS_ACC3(0,0)];
  output[10]= pressure[OPS_ACC4(0,0)];
  output[11]= soundspeed[OPS_ACC5(0,0)];

}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5


void calc_dt_kernel_print_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  double *p_a3,
  double *p_a4,
  double *p_a5,
  double *p_a6,
  int x_size, int y_size) {
  double p_a6_l[12];
  for (int d = 0; d < 12; d++) p_a6_l[d] = p_a6[d];
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1,p_a2,p_a3,p_a4,p_a5) reduction(+:p_a6_l)
  #pragma acc loop reduction(+:p_a6_l)
  #endif
  for ( int n_y=0; n_y<y_size; n_y++ ){
    #ifdef OPS_GPU
    #pragma acc loop reduction(+:p_a6_l)
    #endif
    for ( int n_x=0; n_x<x_size; n_x++ ){
      calc_dt_kernel_print(  p_a0 + n_x*1 + n_y*xdim0_calc_dt_kernel_print*1,
           p_a1 + n_x*1 + n_y*xdim1_calc_dt_kernel_print*1, p_a2 + n_x*1 + n_y*xdim2_calc_dt_kernel_print*1,
           p_a3 + n_x*1 + n_y*xdim3_calc_dt_kernel_print*1, p_a4 + n_x*1 + n_y*xdim4_calc_dt_kernel_print*1,
           p_a5 + n_x*1 + n_y*xdim5_calc_dt_kernel_print*1, p_a6_l );

    }
  }
  for (int d = 0; d < 12; d++) p_a6[d] = p_a6_l[d];
}
