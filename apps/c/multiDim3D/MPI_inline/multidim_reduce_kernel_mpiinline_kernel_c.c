//
// auto-generated by ops.py
//
#include "./MPI_inline/multidim_common.h"

int xdim0_multidim_reduce_kernel;
int ydim0_multidim_reduce_kernel;
int zdim0_multidim_reduce_kernel;

#define OPS_ACC_MD0(d, x, y, z)                                                \
  (n_x * 1 + n_y * xdim0_multidim_reduce_kernel * 1 +                          \
   n_z * xdim0_multidim_reduce_kernel * ydim0_multidim_reduce_kernel * 1 +     \
   (x) +                                                                       \
   (d)*xdim0_multidim_reduce_kernel * ydim0_multidim_reduce_kernel *           \
       zdim0_multidim_reduce_kernel +                                          \
   (xdim0_multidim_reduce_kernel * (y)) +                                      \
   (xdim0_multidim_reduce_kernel * ydim0_multidim_reduce_kernel * (z)))
// user function

void multidim_reduce_kernel_c_wrapper(const double *restrict val,
                                      double *restrict redu_dat1_g, int x_size,
                                      int y_size, int z_size) {
  double redu_dat1_v = *redu_dat1_g;
#pragma omp parallel for reduction(+ : redu_dat1_v)
  for (int n_z = 0; n_z < z_size; n_z++) {
    for (int n_y = 0; n_y < y_size; n_y++) {
      for (int n_x = 0; n_x < x_size; n_x++) {
        double *restrict redu_dat1 = &redu_dat1_v;

        redu_dat1[0] = redu_dat1[0] + val[OPS_ACC_MD0(0, 0, 0, 0)];
        redu_dat1[1] = redu_dat1[1] + val[OPS_ACC_MD0(1, 0, 0, 0)];
        redu_dat1[2] = redu_dat1[2] + val[OPS_ACC_MD0(2, 0, 0, 0)];
      }
    }
  }
  *redu_dat1_g = redu_dat1_v;
}

#undef OPS_ACC_MD0
