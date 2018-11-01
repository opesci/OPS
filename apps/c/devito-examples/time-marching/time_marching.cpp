#include <stdlib.h>
#include <stdio.h>

int nx, ny, nt;

//Including main OPS header file, and setting 2D
#define OPS_2D
#include "ops_seq.h"

#define OUTPUT_FILE "output.txt"

//Including applicaiton-specific "user kernels"
#include "time_marching_kernel.h"

int main(int argc, char *argv[])
{
    int size[2];
    int base[] = {0, 0};
    int d_m[] = {0, 0};
    int d_p[] = {0, 0};
    double **u;

    if (argc != 2)
    {
        printf("Expected argument:\t1) - Number of time steps (nt)\n");
        return -1;
    }

    ops_init(argc, argv, 1);

    // Set dimension parameters
    nx = ny = 10;
    nt = atoi(argv[1]);

    size[0] = nx;
    size[1] = ny;

    // Declare global constant
    ops_decl_const("nx", 1, "int", &nx);
    ops_decl_const("ny", 1, "int", &ny);

    // Alocates and initialize grid
    u = (double **)malloc(2 * sizeof(double *));
    u[0] = (double *)calloc(nx * ny, sizeof(double));
    u[1] = (double *)calloc(nx * ny, sizeof(double));

    // Declare an ops_block
    ops_block grid = ops_decl_block(2, "grid");

    // Declare an ops_dat object
    ops_dat dat_u[2];
    dat_u[0] = ops_decl_dat(grid, 1, size, base, d_m, d_p, u[0], "double", "u0");
    dat_u[1] = ops_decl_dat(grid, 1, size, base, d_m, d_p, u[1], "double", "u1");

    // Print dat to text file for debugging
    ops_print_dat_to_txtfile(dat_u[0], OUTPUT_FILE);
    ops_print_dat_to_txtfile(dat_u[1], OUTPUT_FILE);

    // Declare stencil
    int s2d_00[] = {0, 0};
    ops_stencil S2D_00 = ops_decl_stencil(2, 1, s2d_00, "00");

    // Set loop iteration range to be all the grid.
    int iter_range[] = {0, nx, 0, ny};

    printf("Starts time propagation.\n");

    for (int i = 0; i < nt; i++)
    {
        ops_par_loop(march_kernel, "march_kernel", grid, 2, iter_range,
                     ops_arg_dat(dat_u[i % 2], 1, S2D_00, "double", OPS_WRITE),
                     ops_arg_dat(dat_u[(i + 1) % 2], 1, S2D_00, "double", OPS_READ));
    }

    printf("Propagation finished.\n");

    // Print dat to text file for debugging
    ops_dat_fetch_data(dat_u[0], 0, (char *)u[0]);
    ops_dat_fetch_data(dat_u[1], 0, (char *)u[1]);

    // Print dat to text file for debugging
    ops_print_dat_to_txtfile(dat_u[0], OUTPUT_FILE);
    ops_print_dat_to_txtfile(dat_u[1], OUTPUT_FILE);

    printf("Output generated in file: %s", OUTPUT_FILE);

    ops_exit();

    return 0;
}
