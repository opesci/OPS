//
// auto-generated by ops.py
//



void ops_init_backend();
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define OPS_2D

#include  "ops_lib_cpp.h"

//
// ops_par_loop declarations
//

void ops_par_loop_random_print_kernel(char const *, ops_block, int , int*,
  ops_arg );



//#include "random_print_kernel.h"

int main(int argc, char **argv)
{

  int x_cells = 4;
  int y_cells = 4;


  ops_init(argc,argv,1);
  ops_init_backend();



  ops_block grid2D = ops_decl_block(2, "grid2D");

  int s2D_00[]         = {0,0};
  ops_stencil S2D_00 = ops_decl_stencil( 2, 1, s2D_00, "00");

  int d_p[2] = {2,1};
  int d_m[2] = {-2,-1};
  int size[2] = {x_cells, y_cells};
  int base[2] = {0,0};
  double* temp = NULL;

  ops_dat dat0    = ops_decl_dat(grid2D, 2, size, base, d_m, d_p, temp, "double", "dat0");

  ops_partition("2D_BLOCK_DECOMPSE");

  double ct0, ct1, et0, et1;
  ops_timers(&ct0, &et0);

  ops_random_init(0, 0);
  ops_fill_random_uniform(dat0);

  int iter_range[] = {0,4,0,4};
  ops_par_loop_random_print_kernel("random_print_kernel", grid2D, 2, iter_range,
               ops_arg_dat(dat0, 2, S2D_00, "double", OPS_READ));

  ops_timers(&ct1, &et1);
  ops_print_dat_to_txtfile(dat0, "random.dat");

  ops_printf("\nTotal Wall time %lf\n",et1-et0);
  ops_printf("This run is considered PASSED\n");

  ops_exit();
  return 0;
}