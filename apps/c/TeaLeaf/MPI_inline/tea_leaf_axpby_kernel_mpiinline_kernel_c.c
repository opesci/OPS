//
// auto-generated by ops.py
//

int xdim0_tea_leaf_axpby_kernel;
int xdim1_tea_leaf_axpby_kernel;


//user function

void tea_leaf_axpby_kernel_c_wrapper(double *restrict u_p, double *restrict p_p,
                                     const double *restrict alpha,
                                     const double *restrict beta, int x_size,
                                     int y_size) {
#pragma omp parallel for
  for ( int n_y=0; n_y<y_size; n_y++ ){
    for ( int n_x=0; n_x<x_size; n_x++ ){
      ptr_double u = {u_p + n_x * 1 + n_y * xdim0_tea_leaf_axpby_kernel * 1,
                      xdim0_tea_leaf_axpby_kernel};
      const ptr_double p = {p_p + n_x * 1 +
                                n_y * xdim1_tea_leaf_axpby_kernel * 1,
                            xdim1_tea_leaf_axpby_kernel};

      OPS_ACC(u, 0, 0) =
          (*alpha) * OPS_ACC(u, 0, 0) + (*beta) * OPS_ACC(p, 0, 0);
    }
  }
}
