//
// auto-generated by ops.py
//
#include "./OpenMP4/clover_leaf_common.h"
#include <omp.h>
#define OPS_GPU

extern int xdim0_advec_mom_kernel_mass_flux_y;
extern int xdim1_advec_mom_kernel_mass_flux_y;

#undef OPS_ACC0
#undef OPS_ACC1

#define OPS_ACC0(x, y)                                                         \
  (n_x * 1 * 1 + n_y * xdim0_advec_mom_kernel_mass_flux_y * 1 * 1 + x +        \
   xdim0_advec_mom_kernel_mass_flux_y * (y))
#define OPS_ACC1(x, y)                                                         \
  (n_x * 1 * 1 + n_y * xdim1_advec_mom_kernel_mass_flux_y * 1 * 1 + x +        \
   xdim1_advec_mom_kernel_mass_flux_y * (y))

// user function

void advec_mom_kernel_mass_flux_y_c_wrapper(double *p_a0, double *p_a1,
                                            int x_size, int y_size) {
#ifdef OPS_GPU

#pragma omp target teams distribute parallel for schedule(static, 1)
#endif
  for (int i = 0; i < y_size * x_size; i++) {
    int n_x = i % x_size;
    int n_y = i / x_size;
    double *node_flux = p_a0;

    const double *mass_flux_y = p_a1;

    node_flux[OPS_ACC0(0, 0)] =
        0.25 * (mass_flux_y[OPS_ACC1(-1, 0)] + mass_flux_y[OPS_ACC1(0, 0)] +
                mass_flux_y[OPS_ACC1(-1, 1)] + mass_flux_y[OPS_ACC1(0, 1)]);
  }
}
#undef OPS_ACC0
#undef OPS_ACC1