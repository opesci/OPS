//
<<<<<<< HEAD
// auto-generated by ops.py on 2014-07-28 13:08
=======
// auto-generated by ops.py on 2014-07-31 11:59
>>>>>>> d8a3b1f... 2D Cloverleaf OpenCL works with MPI's seq files
//



#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include  "ops_lib_cpp.h"

//
// ops_par_loop declarations
//

void ops_par_loop_flux_calc_kernelx(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );

void ops_par_loop_flux_calc_kernely(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );



#include "data.h"
#include "definitions.h"

//#include "flux_calc_kernel.h"

void flux_calc()
{
  error_condition = 0;

  int x_cells = grid.x_cells;
  int y_cells = grid.y_cells;
  int x_min = field.x_min;
  int x_max = field.x_max;
  int y_min = field.y_min;
  int y_max = field.y_max;

  int rangexy_inner_plus1x[] = {x_min,x_max+1,y_min,y_max};

  ops_par_loop_flux_calc_kernelx("flux_calc_kernelx", clover_grid, 2, rangexy_inner_plus1x,
               ops_arg_dat(vol_flux_x, S2D_00, "double", OPS_WRITE),
               ops_arg_dat(xarea, S2D_00, "double", OPS_READ),
               ops_arg_dat(xvel0, S2D_00_0P1, "double", OPS_READ),
               ops_arg_dat(xvel1, S2D_00_0P1, "double", OPS_READ));

  int rangexy_inner_plus1y[] = {x_min,x_max,y_min,y_max+1};

  ops_par_loop_flux_calc_kernely("flux_calc_kernely", clover_grid, 2, rangexy_inner_plus1y,
               ops_arg_dat(vol_flux_y, S2D_00, "double", OPS_WRITE),
               ops_arg_dat(yarea, S2D_00, "double", OPS_READ),
               ops_arg_dat(yvel0, S2D_00_P10, "double", OPS_READ),
               ops_arg_dat(yvel1, S2D_00_P10, "double", OPS_READ));

}
