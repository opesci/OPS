//
// auto-generated by ops.py//

// header
#define OPS_2D
#define OPS_ACC_MD_MACROS
#include "ops_lib_cpp.h"
#ifdef OPS_MPI
#include "ops_mpi_core.h"
#endif

// global constants
extern double dx;
extern double dy;

void ops_init_backend() {}

// user kernel files
#include "poisson_kernel_error_seq_kernel.cpp"
#include "poisson_kernel_initialguess_seq_kernel.cpp"
#include "poisson_kernel_populate_seq_kernel.cpp"
#include "poisson_kernel_stencil_seq_kernel.cpp"
#include "poisson_kernel_update_seq_kernel.cpp"
