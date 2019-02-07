//
// auto-generated by ops.py
//

int xdim0_update_halo_kernel2_xvel_plus_2_back;
int ydim0_update_halo_kernel2_xvel_plus_2_back;
int xdim1_update_halo_kernel2_xvel_plus_2_back;
int ydim1_update_halo_kernel2_xvel_plus_2_back;

#define OPS_ACC0(x, y, z)                                                      \
  (n_x * 1 + n_y * xdim0_update_halo_kernel2_xvel_plus_2_back * 1 +            \
   n_z * xdim0_update_halo_kernel2_xvel_plus_2_back *                          \
       ydim0_update_halo_kernel2_xvel_plus_2_back * 1 +                        \
   x + xdim0_update_halo_kernel2_xvel_plus_2_back * (y) +                      \
   xdim0_update_halo_kernel2_xvel_plus_2_back *                                \
       ydim0_update_halo_kernel2_xvel_plus_2_back * (z))
#define OPS_ACC1(x, y, z)                                                      \
  (n_x * 1 + n_y * xdim1_update_halo_kernel2_xvel_plus_2_back * 1 +            \
   n_z * xdim1_update_halo_kernel2_xvel_plus_2_back *                          \
       ydim1_update_halo_kernel2_xvel_plus_2_back * 1 +                        \
   x + xdim1_update_halo_kernel2_xvel_plus_2_back * (y) +                      \
   xdim1_update_halo_kernel2_xvel_plus_2_back *                                \
       ydim1_update_halo_kernel2_xvel_plus_2_back * (z))

// user function

void update_halo_kernel2_xvel_plus_2_back_c_wrapper(double *restrict xvel0,
                                                    double *restrict xvel1,
                                                    const int *restrict fields,
                                                    int x_size, int y_size,
                                                    int z_size) {
#pragma omp parallel for
  for (int n_z = 0; n_z < z_size; n_z++) {
    for (int n_y = 0; n_y < y_size; n_y++) {
      for (int n_x = 0; n_x < x_size; n_x++) {

        if (fields[FIELD_XVEL0] == 1)
          xvel0[OPS_ACC0(0, 0, 0)] = xvel0[OPS_ACC0(0, 0, 2)];
        if (fields[FIELD_XVEL1] == 1)
          xvel1[OPS_ACC1(0, 0, 0)] = xvel1[OPS_ACC1(0, 0, 2)];
      }
    }
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
