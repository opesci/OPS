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

void ops_par_loop_revert_kernel(char const *, ops_block, int , int*,
  ops_arg,
  ops_arg,
  ops_arg,
  ops_arg );



#include "data.h"
#include "definitions.h"

//#include "revert_kernel.h"

void revert()
{
  error_condition = 0;

  int x_cells = grid.x_cells;
  int y_cells = grid.y_cells;
  int x_min = field.x_min;
  int x_max = field.x_max;
  int y_min = field.y_min;
  int y_max = field.y_max;

  int rangexy_inner[] = {x_min,x_max,y_min,y_max};

  ops_par_loop_revert_kernel("revert_kernel", clover_grid, 2, rangexy_inner,
               ops_arg_dat(density0, S2D_00, "double", OPS_READ),
               ops_arg_dat(density1, S2D_00, "double", OPS_WRITE),
               ops_arg_dat(energy0, S2D_00, "double", OPS_READ),
               ops_arg_dat(energy1, S2D_00, "double", OPS_WRITE));
}
