//
// auto-generated by ops.py//




#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define OPS_2D
#include  "ops_lib_cpp.h"

//
// ops_par_loop declarations
//

void ops_par_loop_multidim_kernel(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg );

void ops_par_loop_multidim_copy_kernel(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg );

void ops_par_loop_multidim_reduce_kernel(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg );



//#include "multidim_kernel.h"
//#include "multidim_print_kernel.h"
//#include "multidim_copy_kernel.h"
//#include "multidim_reduce_kernel.h"

int main(int argc, char **argv)
{

  int x_cells = 4;
  int y_cells = 4;


  ops_init(argc,argv,1);


  ops_block grid2D = ops_decl_block(2, "grid2D");

  int s2D_00[]         = {0,0};
  ops_stencil S2D_00 = ops_decl_stencil( 2, 1, s2D_00, "00");


  int d_p[2] = {1,1};
  int d_m[2] = {-1,-1};
  int size[2] = {x_cells, y_cells};
  int base[2] = {0,0};
  double* temp = NULL;

  ops_dat dat0    = ops_decl_dat(grid2D, 2, size, base, d_m, d_p, temp, "double", "dat0");
  ops_dat dat1    = ops_decl_dat(grid2D, 2, size, base, d_m, d_p, temp, "double", "dat1");

  double reduct_result[2] = {0.0, 0.0};
  ops_reduction reduct_dat1 = ops_decl_reduction_handle(2*sizeof(double), "double", "reduct_dat1");

  ops_partition("2D_BLOCK_DECOMPSE");






  double ct0, ct1, et0, et1;
  ops_timers(&ct0, &et0);

  int iter_range[] = {0,4,0,4};
  ops_par_loop_multidim_kernel("multidim_kernel", grid2D, 2, iter_range,
               ops_arg_dat(dat0, 2, S2D_00, "double", OPS_WRITE),
               ops_arg_idx());
  ops_par_loop_multidim_copy_kernel("multidim_copy_kernel", grid2D, 2, iter_range,
               ops_arg_dat(dat0, 2, S2D_00, "double", OPS_READ),
               ops_arg_dat(dat1, 2, S2D_00, "double", OPS_WRITE));




  ops_par_loop_multidim_reduce_kernel("multidim_reduce_kernel", grid2D, 2, iter_range,
               ops_arg_dat(dat1, 2, S2D_00, "double", OPS_READ),
               ops_arg_reduce(reduct_dat1, 2, "double", OPS_INC));

  ops_reduction_result(reduct_dat1, reduct_result);
  ops_printf("Reduction result = %lf, %lf", reduct_result[0],reduct_result[1]);

  ops_timers(&ct1, &et1);
  ops_print_dat_to_txtfile(dat0, "multidim.dat");

  ops_fetch_block_hdf5_file(grid2D, "multidim.h5");
  ops_fetch_dat_hdf5_file(dat0, "multidim.h5");

  ops_printf("\nTotal Wall time %lf\n",et1-et0);

  ops_exit();
}
