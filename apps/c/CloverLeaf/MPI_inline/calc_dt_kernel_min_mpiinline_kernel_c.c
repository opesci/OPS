//
// auto-generated by ops.py
//

int xdim0_calc_dt_kernel_min;


#define OPS_ACC0(x,y) (n_x*1+n_y*xdim0_calc_dt_kernel_min*1+x+xdim0_calc_dt_kernel_min*(y))

//user function



void calc_dt_kernel_min_c_wrapper(
  const double * restrict dt_min,
  double * restrict dt_min_val_g,
  int x_size, int y_size) {
  double dt_min_val_v = *dt_min_val_g;
  #pragma omp parallel for reduction(min:dt_min_val_v)
  for ( int n_y=0; n_y<y_size; n_y++ ){
    for ( int n_x=0; n_x<x_size; n_x++ ){
      double * restrict dt_min_val = &dt_min_val_v;
      
  *dt_min_val = MIN(*dt_min_val, dt_min[OPS_ACC0(0,0)]);


    }
  }
  *dt_min_val_g = dt_min_val_v;
}
#undef OPS_ACC0

