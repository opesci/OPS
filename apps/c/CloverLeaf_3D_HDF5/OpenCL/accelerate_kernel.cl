//
// auto-generated by ops.py
//

#ifdef OCL_FMA
#pragma OPENCL FP_CONTRACT ON
#else
#pragma OPENCL FP_CONTRACT OFF
#endif
#pragma OPENCL EXTENSION cl_khr_fp64:enable

#include "user_types.h"
#define OPS_3D
#define OPS_API 2
#define OPS_NO_GLOBALS
#include "ops_macros.h"
#include "ops_opencl_reduction.h"

#ifndef MIN
#define MIN(a,b) ((a<b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a,b) ((a>b) ? (a) : (b))
#endif
#ifndef SIGN
#define SIGN(a,b) ((b<0.0) ? (a*(-1)) : (a))
#endif
#define OPS_READ 0
#define OPS_WRITE 1
#define OPS_RW 2
#define OPS_INC 3
#define OPS_MIN 4
#define OPS_MAX 5
#define ZERO_double 0.0;
#define INFINITY_double INFINITY;
#define ZERO_float 0.0f;
#define INFINITY_float INFINITY;
#define ZERO_int 0;
#define INFINITY_int INFINITY;
#define ZERO_uint 0;
#define INFINITY_uint INFINITY;
#define ZERO_ll 0;
#define INFINITY_ll INFINITY;
#define ZERO_ull 0;
#define INFINITY_ull INFINITY;
#define ZERO_bool 0;

//user function

void accelerate_kernel(const ptr_double density0,
  const ptr_double volume,
  ptr_double stepbymass,
  const ptr_double xvel0,
  ptr_double xvel1,
  const ptr_double xarea,
  const ptr_double pressure,
  const ptr_double yvel0,
  ptr_double yvel1,
  const ptr_double yarea,
  const ptr_double viscosity,
  const ptr_double zvel0,
  ptr_double zvel1,
  const ptr_double zarea, const double dt)
{

  double nodal_mass = 0.0;
  nodal_mass =(OPS_ACCS(density0, -1,-1, 0) * OPS_ACCS(volume, -1,-1, 0) +
               OPS_ACCS(density0,  0,-1, 0) * OPS_ACCS(volume,  0,-1, 0) +
               OPS_ACCS(density0,  0, 0, 0) * OPS_ACCS(volume,  0, 0, 0) +
               OPS_ACCS(density0, -1, 0, 0) * OPS_ACCS(volume, -1, 0, 0) +
               OPS_ACCS(density0, -1,-1,-1) * OPS_ACCS(volume, -1,-1,-1) +
               OPS_ACCS(density0,  0,-1,-1) * OPS_ACCS(volume,  0,-1,-1) +
               OPS_ACCS(density0,  0, 0,-1) * OPS_ACCS(volume,  0, 0,-1) +
               OPS_ACCS(density0, -1, 0,-1) * OPS_ACCS(volume, -1, 0,-1)) * 0.125;

  OPS_ACCS(stepbymass, 0,0,0) = 0.25*dt / nodal_mass;

  OPS_ACCS(xvel1, 0,0,0) = OPS_ACCS(xvel0, 0,0,0) - OPS_ACCS(stepbymass, 0,0,0) *
            ( OPS_ACCS(xarea, 0,0,0)  * ( OPS_ACCS(pressure, 0,0,0) - OPS_ACCS(pressure, -1,0,0) ) +
              OPS_ACCS(xarea, 0,-1,0) * ( OPS_ACCS(pressure, 0,-1,0) - OPS_ACCS(pressure, -1,-1,0) ) +
              OPS_ACCS(xarea, 0,0,-1) * ( OPS_ACCS(pressure, 0,0,-1) - OPS_ACCS(pressure, -1,0,-1) ) +
              OPS_ACCS(xarea, 0,-1,-1) * ( OPS_ACCS(pressure, 0,-1,-1) - OPS_ACCS(pressure, -1,-1,-1) ) );

  OPS_ACCS(yvel1, 0,0,0) = OPS_ACCS(yvel0, 0,0,0) - OPS_ACCS(stepbymass, 0,0,0) *
            ( OPS_ACCS(yarea, 0,0,0)  * ( OPS_ACCS(pressure, 0,0,0) - OPS_ACCS(pressure, 0,-1,0) ) +
              OPS_ACCS(yarea, -1,0,0) * ( OPS_ACCS(pressure, -1,0,0) - OPS_ACCS(pressure, -1,-1,0) ) +
              OPS_ACCS(yarea, 0,0,-1) * ( OPS_ACCS(pressure, 0,0,-1) - OPS_ACCS(pressure, 0,-1,-1) ) +
              OPS_ACCS(yarea, -1,0,-1)* ( OPS_ACCS(pressure, -1,0,-1) - OPS_ACCS(pressure, -1,-1,-1) ) );

  OPS_ACCS(zvel1, 0,0,0) = OPS_ACCS(zvel0, 0,0,0) - OPS_ACCS(stepbymass, 0,0,0) *
            ( OPS_ACCS(zarea, 0,0,0)  * ( OPS_ACCS(pressure, 0,0,0) - OPS_ACCS(pressure, 0,0,-1) ) +
              OPS_ACCS(zarea, 0,-1,0) * ( OPS_ACCS(pressure, 0,-1,0) - OPS_ACCS(pressure, 0,-1,-1) ) +
              OPS_ACCS(zarea, -1,0,0) * ( OPS_ACCS(pressure, -1,0,0) - OPS_ACCS(pressure, -1,0,-1) ) +
              OPS_ACCS(zarea, -1,-1,0)* ( OPS_ACCS(pressure, -1,-1,0) - OPS_ACCS(pressure, -1,-1,-1) ) );

  OPS_ACCS(xvel1, 0,0,0) = OPS_ACCS(xvel1, 0,0,0) - OPS_ACCS(stepbymass, 0,0,0) *
            ( OPS_ACCS(xarea, 0,0,0)  * ( OPS_ACCS(viscosity, 0,0,0) - OPS_ACCS(viscosity, -1,0,0) ) +
              OPS_ACCS(xarea, 0,-1,0) * ( OPS_ACCS(viscosity, 0,-1,0) - OPS_ACCS(viscosity, -1,-1,0) ) +
              OPS_ACCS(xarea, 0,0,-1) * ( OPS_ACCS(viscosity, 0,0,-1) - OPS_ACCS(viscosity, -1,0,-1) ) +
              OPS_ACCS(xarea, 0,-1,-1)* ( OPS_ACCS(viscosity, 0,-1,-1) - OPS_ACCS(viscosity, -1,-1,-1) ) );

  OPS_ACCS(yvel1, 0,0,0) = OPS_ACCS(yvel1, 0,0,0) - OPS_ACCS(stepbymass, 0,0,0) *
            ( OPS_ACCS(yarea, 0,0,0)  * ( OPS_ACCS(viscosity, 0,0,0)  - OPS_ACCS(viscosity, 0,-1,0) ) +
              OPS_ACCS(yarea, -1,0,0) * ( OPS_ACCS(viscosity, -1,0,0) - OPS_ACCS(viscosity, -1,-1,0) ) +
              OPS_ACCS(yarea, 0,0,-1) * ( OPS_ACCS(viscosity, 0,0,-1) - OPS_ACCS(viscosity, 0,-1,-1) ) +
              OPS_ACCS(yarea, -1,0,-1)* ( OPS_ACCS(viscosity, -1,0,-1)- OPS_ACCS(viscosity, -1,-1,-1) ) );

  OPS_ACCS(zvel1, 0,0,0) = OPS_ACCS(zvel1, 0,0,0) - OPS_ACCS(stepbymass, 0,0,0) *
            ( OPS_ACCS(zarea, 0,0,0)  * ( OPS_ACCS(viscosity, 0,0,0)  - OPS_ACCS(viscosity, 0,0,-1) ) +
              OPS_ACCS(zarea, 0,-1,0) * ( OPS_ACCS(viscosity, 0,-1,0) - OPS_ACCS(viscosity, 0,-1,-1) ) +
              OPS_ACCS(zarea, -1,0,0) * ( OPS_ACCS(viscosity, -1,0,0) - OPS_ACCS(viscosity, -1,0,-1) ) +
              OPS_ACCS(zarea, -1,-1,0)* ( OPS_ACCS(viscosity, -1,-1,0)- OPS_ACCS(viscosity, -1,-1,-1) ) );
}


__kernel void ops_accelerate_kernel(
__global const double* restrict arg0,
__global const double* restrict arg1,
__global double* restrict arg2,
__global const double* restrict arg3,
__global double* restrict arg4,
__global const double* restrict arg5,
__global const double* restrict arg6,
__global const double* restrict arg7,
__global double* restrict arg8,
__global const double* restrict arg9,
__global const double* restrict arg10,
__global const double* restrict arg11,
__global double* restrict arg12,
__global const double* restrict arg13,
const double dt,
const int base0,
const int base1,
const int base2,
const int base3,
const int base4,
const int base5,
const int base6,
const int base7,
const int base8,
const int base9,
const int base10,
const int base11,
const int base12,
const int base13,
const int size0,
const int size1,
const int size2 ){


  int idx_y = get_global_id(1);
  int idx_z = get_global_id(2);
  int idx_x = get_global_id(0);

  if (idx_x < size0 && idx_y < size1 && idx_z < size2) {
    const ptr_double ptr0 = { &arg0[base0 + idx_x * 1*1 + idx_y * 1*1 * xdim0_accelerate_kernel + idx_z * 1*1 * xdim0_accelerate_kernel * ydim0_accelerate_kernel], xdim0_accelerate_kernel, ydim0_accelerate_kernel};
    const ptr_double ptr1 = { &arg1[base1 + idx_x * 1*1 + idx_y * 1*1 * xdim1_accelerate_kernel + idx_z * 1*1 * xdim1_accelerate_kernel * ydim1_accelerate_kernel], xdim1_accelerate_kernel, ydim1_accelerate_kernel};
    ptr_double ptr2 = { &arg2[base2 + idx_x * 1*1 + idx_y * 1*1 * xdim2_accelerate_kernel + idx_z * 1*1 * xdim2_accelerate_kernel * ydim2_accelerate_kernel], xdim2_accelerate_kernel, ydim2_accelerate_kernel};
    const ptr_double ptr3 = { &arg3[base3 + idx_x * 1*1 + idx_y * 1*1 * xdim3_accelerate_kernel + idx_z * 1*1 * xdim3_accelerate_kernel * ydim3_accelerate_kernel], xdim3_accelerate_kernel, ydim3_accelerate_kernel};
    ptr_double ptr4 = { &arg4[base4 + idx_x * 1*1 + idx_y * 1*1 * xdim4_accelerate_kernel + idx_z * 1*1 * xdim4_accelerate_kernel * ydim4_accelerate_kernel], xdim4_accelerate_kernel, ydim4_accelerate_kernel};
    const ptr_double ptr5 = { &arg5[base5 + idx_x * 1*1 + idx_y * 1*1 * xdim5_accelerate_kernel + idx_z * 1*1 * xdim5_accelerate_kernel * ydim5_accelerate_kernel], xdim5_accelerate_kernel, ydim5_accelerate_kernel};
    const ptr_double ptr6 = { &arg6[base6 + idx_x * 1*1 + idx_y * 1*1 * xdim6_accelerate_kernel + idx_z * 1*1 * xdim6_accelerate_kernel * ydim6_accelerate_kernel], xdim6_accelerate_kernel, ydim6_accelerate_kernel};
    const ptr_double ptr7 = { &arg7[base7 + idx_x * 1*1 + idx_y * 1*1 * xdim7_accelerate_kernel + idx_z * 1*1 * xdim7_accelerate_kernel * ydim7_accelerate_kernel], xdim7_accelerate_kernel, ydim7_accelerate_kernel};
    ptr_double ptr8 = { &arg8[base8 + idx_x * 1*1 + idx_y * 1*1 * xdim8_accelerate_kernel + idx_z * 1*1 * xdim8_accelerate_kernel * ydim8_accelerate_kernel], xdim8_accelerate_kernel, ydim8_accelerate_kernel};
    const ptr_double ptr9 = { &arg9[base9 + idx_x * 1*1 + idx_y * 1*1 * xdim9_accelerate_kernel + idx_z * 1*1 * xdim9_accelerate_kernel * ydim9_accelerate_kernel], xdim9_accelerate_kernel, ydim9_accelerate_kernel};
    const ptr_double ptr10 = { &arg10[base10 + idx_x * 1*1 + idx_y * 1*1 * xdim10_accelerate_kernel + idx_z * 1*1 * xdim10_accelerate_kernel * ydim10_accelerate_kernel], xdim10_accelerate_kernel, ydim10_accelerate_kernel};
    const ptr_double ptr11 = { &arg11[base11 + idx_x * 1*1 + idx_y * 1*1 * xdim11_accelerate_kernel + idx_z * 1*1 * xdim11_accelerate_kernel * ydim11_accelerate_kernel], xdim11_accelerate_kernel, ydim11_accelerate_kernel};
    ptr_double ptr12 = { &arg12[base12 + idx_x * 1*1 + idx_y * 1*1 * xdim12_accelerate_kernel + idx_z * 1*1 * xdim12_accelerate_kernel * ydim12_accelerate_kernel], xdim12_accelerate_kernel, ydim12_accelerate_kernel};
    const ptr_double ptr13 = { &arg13[base13 + idx_x * 1*1 + idx_y * 1*1 * xdim13_accelerate_kernel + idx_z * 1*1 * xdim13_accelerate_kernel * ydim13_accelerate_kernel], xdim13_accelerate_kernel, ydim13_accelerate_kernel};
    accelerate_kernel(ptr0,
                      ptr1,
                      ptr2,
                      ptr3,
                      ptr4,
                      ptr5,
                      ptr6,
                      ptr7,
                      ptr8,
                      ptr9,
                      ptr10,
                      ptr11,
                      ptr12,
                      ptr13,
                      dt);
  }

}
