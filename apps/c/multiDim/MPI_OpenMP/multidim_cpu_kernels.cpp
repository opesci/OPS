//
// auto-generated by ops.py//

//header
#define OPS_2D
#define OPS_SOA
#define OPS_API 2
#include "ops_lib_cpp.h"
#ifdef OPS_MPI
#include "ops_mpi_core.h"
#endif

// global constants

void ops_init_backend() {}

//user kernel files
#include "multidim_kernel_cpu_kernel.cpp"
#include "multidim_copy_kernel_cpu_kernel.cpp"
#include "multidim_reduce_kernel_cpu_kernel.cpp"