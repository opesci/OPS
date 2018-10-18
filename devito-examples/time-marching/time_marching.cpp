#include <stdlib.h>
#include <stdio.h>

int nx, ny, nt;

//Including main OPS header file, and setting 2D
#define OPS_2D
#include "ops_seq.h"

#define Item ops_dat
#define swap(a, b)     \
    {                  \
        Item temp = a; \
        a = b;         \
        b = temp;      \
    }

//Including applicaiton-specific "user kernels"
#include "time_marching_kernel.h"

int main(int argc, char *argv[])
{
    int size[2];
    int base[] = {0, 0};
    int d_m[] = {0, 0};
    int d_p[] = {0, 0};
    double *u0, *un;

    if (argc != 2)
    {
        printf("Argumento:\t1) - nt\n");
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
    u0 = (double *)calloc(nx * ny, sizeof(double));
    un = (double *)calloc(nx * ny, sizeof(double));

    // Declare an ops_block
    ops_block grid = ops_decl_block(2, "grid");

    // Declare an ops_dat object
    ops_dat dat_u0 = ops_decl_dat(grid, 1, size, base, d_m, d_p, u0, "double", "u0");
    ops_dat dat_un = ops_decl_dat(grid, 1, size, base, d_m, d_p, un, "double", "un");

    // Print dat to text file for debugging
    ops_print_dat_to_txtfile(dat_u0, "output.txt");
    ops_print_dat_to_txtfile(dat_un, "output.txt");

    // Declare stencil
    int s2d_00[] = {0, 0};
    ops_stencil S2D_00 = ops_decl_stencil(2, 1, s2d_00, "00");

    // Set loop iteration range to be all the grid.
    int iter_range[] = {0, nx, 0, ny};

    for (int i = 0; i < nt; i++)
    {
        ops_par_loop(march_kernel, "march_kernel", grid, 2, iter_range,
                     ops_arg_dat(dat_un, 1, S2D_00, "double", OPS_WRITE),
                     ops_arg_dat(dat_u0, 1, S2D_00, "double", OPS_READ));

        swap(dat_un, dat_u0);
    }

    printf("\n------------------------\n");
    printf("u0 - %lf\n", u0[0]);
    printf("un - %lf\n", un[0]);

    if ((nt % 2) == 1)
    {
        swap(dat_un, dat_u0);
    }

    // Print dat to text file for debugging
    ops_print_dat_to_txtfile(dat_u0, "output.txt");
    ops_print_dat_to_txtfile(dat_un, "output.txt");

    // Print dat to text file for debugging
    ops_dat_fetch_data(dat_u0, 0, (char *)u0);
    ops_dat_fetch_data(dat_un, 0, (char *)un);

    printf("u0 - %lf\n", u0[0]);
    printf("un - %lf\n", un[0]);

    ops_exit();

    return 0;
}
