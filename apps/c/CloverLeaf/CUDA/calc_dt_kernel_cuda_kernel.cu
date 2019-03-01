//
// auto-generated by ops.py
//
__constant__ int xdim0_calc_dt_kernel;
int xdim0_calc_dt_kernel_h = -1;
__constant__ int xdim1_calc_dt_kernel;
int xdim1_calc_dt_kernel_h = -1;
__constant__ int xdim2_calc_dt_kernel;
int xdim2_calc_dt_kernel_h = -1;
__constant__ int xdim3_calc_dt_kernel;
int xdim3_calc_dt_kernel_h = -1;
__constant__ int xdim4_calc_dt_kernel;
int xdim4_calc_dt_kernel_h = -1;
__constant__ int xdim5_calc_dt_kernel;
int xdim5_calc_dt_kernel_h = -1;
__constant__ int xdim6_calc_dt_kernel;
int xdim6_calc_dt_kernel_h = -1;
__constant__ int xdim7_calc_dt_kernel;
int xdim7_calc_dt_kernel_h = -1;
__constant__ int xdim8_calc_dt_kernel;
int xdim8_calc_dt_kernel_h = -1;
__constant__ int xdim9_calc_dt_kernel;
int xdim9_calc_dt_kernel_h = -1;
__constant__ int xdim10_calc_dt_kernel;
int xdim10_calc_dt_kernel_h = -1;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7
#undef OPS_ACC8
#undef OPS_ACC9
#undef OPS_ACC10

#define OPS_ACC0(x, y) (x + xdim0_calc_dt_kernel * (y))
#define OPS_ACC1(x, y) (x + xdim1_calc_dt_kernel * (y))
#define OPS_ACC2(x, y) (x + xdim2_calc_dt_kernel * (y))
#define OPS_ACC3(x, y) (x + xdim3_calc_dt_kernel * (y))
#define OPS_ACC4(x, y) (x + xdim4_calc_dt_kernel * (y))
#define OPS_ACC5(x, y) (x + xdim5_calc_dt_kernel * (y))
#define OPS_ACC6(x, y) (x + xdim6_calc_dt_kernel * (y))
#define OPS_ACC7(x, y) (x + xdim7_calc_dt_kernel * (y))
#define OPS_ACC8(x, y) (x + xdim8_calc_dt_kernel * (y))
#define OPS_ACC9(x, y) (x + xdim9_calc_dt_kernel * (y))
#define OPS_ACC10(x, y) (x + xdim10_calc_dt_kernel * (y))

// user function
__device__

    void
    calc_dt_kernel_gpu(const double *celldx, const double *celldy,
                       const double *soundspeed, const double *viscosity,
                       const double *density0, const double *xvel0,
                       const double *xarea, const double *volume,
                       const double *yvel0, const double *yarea,
                       double *dt_min) {

  double div, dsx, dsy, dtut, dtvt, dtct, dtdivt, cc, dv1, dv2;

  dsx = celldx[OPS_ACC0(0, 0)];
  dsy = celldy[OPS_ACC1(0, 0)];

  cc = soundspeed[OPS_ACC2(0, 0)] * soundspeed[OPS_ACC2(0, 0)];
  cc = cc + 2.0 * viscosity[OPS_ACC3(0, 0)] / density0[OPS_ACC4(0, 0)];
  cc = MAX(sqrt(cc), g_small);

  dtct = dtc_safe * MIN(dsx, dsy) / cc;

  div = 0.0;

  dv1 = (xvel0[OPS_ACC5(0, 0)] + xvel0[OPS_ACC5(0, 1)]) * xarea[OPS_ACC6(0, 0)];
  dv2 = (xvel0[OPS_ACC5(1, 0)] + xvel0[OPS_ACC5(1, 1)]) * xarea[OPS_ACC6(1, 0)];

  div = div + dv2 - dv1;

  dtut = dtu_safe * 2.0 * volume[OPS_ACC7(0, 0)] /
         MAX(MAX(fabs(dv1), fabs(dv2)), g_small * volume[OPS_ACC7(0, 0)]);

  dv1 = (yvel0[OPS_ACC8(0, 0)] + yvel0[OPS_ACC8(1, 0)]) * yarea[OPS_ACC9(0, 0)];
  dv2 = (yvel0[OPS_ACC8(0, 1)] + yvel0[OPS_ACC8(1, 1)]) * yarea[OPS_ACC9(0, 1)];

  div = div + dv2 - dv1;

  dtvt = dtv_safe * 2.0 * volume[OPS_ACC7(0, 0)] /
         MAX(MAX(fabs(dv1), fabs(dv2)), g_small * volume[OPS_ACC7(0, 0)]);

  div = div / (2.0 * volume[OPS_ACC7(0, 0)]);

  if (div < -g_small)
    dtdivt = dtdiv_safe * (-1.0 / div);
  else
    dtdivt = g_big;

  dt_min[OPS_ACC10(0, 0)] = MIN(MIN(dtct, dtut), MIN(dtvt, dtdivt));
}

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7
#undef OPS_ACC8
#undef OPS_ACC9
#undef OPS_ACC10

__global__ void
ops_calc_dt_kernel(const double *__restrict arg0, const double *__restrict arg1,
                   const double *__restrict arg2, const double *__restrict arg3,
                   const double *__restrict arg4, const double *__restrict arg5,
                   const double *__restrict arg6, const double *__restrict arg7,
                   const double *__restrict arg8, const double *__restrict arg9,
                   double *__restrict arg10, int size0, int size1) {

  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 * 1 + idx_y * 0 * 1 * xdim0_calc_dt_kernel;
  arg1 += idx_x * 0 * 1 + idx_y * 1 * 1 * xdim1_calc_dt_kernel;
  arg2 += idx_x * 1 * 1 + idx_y * 1 * 1 * xdim2_calc_dt_kernel;
  arg3 += idx_x * 1 * 1 + idx_y * 1 * 1 * xdim3_calc_dt_kernel;
  arg4 += idx_x * 1 * 1 + idx_y * 1 * 1 * xdim4_calc_dt_kernel;
  arg5 += idx_x * 1 * 1 + idx_y * 1 * 1 * xdim5_calc_dt_kernel;
  arg6 += idx_x * 1 * 1 + idx_y * 1 * 1 * xdim6_calc_dt_kernel;
  arg7 += idx_x * 1 * 1 + idx_y * 1 * 1 * xdim7_calc_dt_kernel;
  arg8 += idx_x * 1 * 1 + idx_y * 1 * 1 * xdim8_calc_dt_kernel;
  arg9 += idx_x * 1 * 1 + idx_y * 1 * 1 * xdim9_calc_dt_kernel;
  arg10 += idx_x * 1 * 1 + idx_y * 1 * 1 * xdim10_calc_dt_kernel;

  if (idx_x < size0 && idx_y < size1) {
    calc_dt_kernel_gpu(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8,
                       arg9, arg10);
  }
}

// host stub function
#ifndef OPS_LAZY
void ops_par_loop_calc_dt_kernel(char const *name, ops_block block, int dim,
                                 int *range, ops_arg arg0, ops_arg arg1,
                                 ops_arg arg2, ops_arg arg3, ops_arg arg4,
                                 ops_arg arg5, ops_arg arg6, ops_arg arg7,
                                 ops_arg arg8, ops_arg arg9, ops_arg arg10) {
#else
void ops_par_loop_calc_dt_kernel_execute(ops_kernel_descriptor *desc) {
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  ops_arg arg2 = desc->args[2];
  ops_arg arg3 = desc->args[3];
  ops_arg arg4 = desc->args[4];
  ops_arg arg5 = desc->args[5];
  ops_arg arg6 = desc->args[6];
  ops_arg arg7 = desc->args[7];
  ops_arg arg8 = desc->args[8];
  ops_arg arg9 = desc->args[9];
  ops_arg arg10 = desc->args[10];
#endif

  // Timing
  double t1, t2, c1, c2;

  ops_arg args[11] = {arg0, arg1, arg2, arg3, arg4, arg5,
                      arg6, arg7, arg8, arg9, arg10};

#if CHECKPOINTING && !OPS_LAZY
  if (!ops_checkpointing_before(args, 11, range, 27))
    return;
#endif

  if (OPS_diags > 1) {
    ops_timing_realloc(27, "calc_dt_kernel");
    OPS_kernels[27].count++;
    ops_timers_core(&c1, &t1);
  }

  // compute locally allocated range for the sub-block
  int start[2];
  int end[2];
#if OPS_MPI && !OPS_LAZY
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned)
    return;
  for (int n = 0; n < 2; n++) {
    start[n] = sb->decomp_disp[n];
    end[n] = sb->decomp_disp[n] + sb->decomp_size[n];
    if (start[n] >= range[2 * n]) {
      start[n] = 0;
    } else {
      start[n] = range[2 * n] - start[n];
    }
    if (sb->id_m[n] == MPI_PROC_NULL && range[2 * n] < 0)
      start[n] = range[2 * n];
    if (end[n] >= range[2 * n + 1]) {
      end[n] = range[2 * n + 1] - sb->decomp_disp[n];
    } else {
      end[n] = sb->decomp_size[n];
    }
    if (sb->id_p[n] == MPI_PROC_NULL &&
        (range[2 * n + 1] > sb->decomp_disp[n] + sb->decomp_size[n]))
      end[n] += (range[2 * n + 1] - sb->decomp_disp[n] - sb->decomp_size[n]);
  }
#else
  for (int n = 0; n < 2; n++) {
    start[n] = range[2 * n];
    end[n] = range[2 * n + 1];
  }
#endif

  int x_size = MAX(0, end[0] - start[0]);
  int y_size = MAX(0, end[1] - start[1]);

  int xdim0 = args[0].dat->size[0];
  int xdim1 = args[1].dat->size[0];
  int xdim2 = args[2].dat->size[0];
  int xdim3 = args[3].dat->size[0];
  int xdim4 = args[4].dat->size[0];
  int xdim5 = args[5].dat->size[0];
  int xdim6 = args[6].dat->size[0];
  int xdim7 = args[7].dat->size[0];
  int xdim8 = args[8].dat->size[0];
  int xdim9 = args[9].dat->size[0];
  int xdim10 = args[10].dat->size[0];

  if (xdim0 != xdim0_calc_dt_kernel_h || xdim1 != xdim1_calc_dt_kernel_h ||
      xdim2 != xdim2_calc_dt_kernel_h || xdim3 != xdim3_calc_dt_kernel_h ||
      xdim4 != xdim4_calc_dt_kernel_h || xdim5 != xdim5_calc_dt_kernel_h ||
      xdim6 != xdim6_calc_dt_kernel_h || xdim7 != xdim7_calc_dt_kernel_h ||
      xdim8 != xdim8_calc_dt_kernel_h || xdim9 != xdim9_calc_dt_kernel_h ||
      xdim10 != xdim10_calc_dt_kernel_h) {
    cudaMemcpyToSymbol(xdim0_calc_dt_kernel, &xdim0, sizeof(int));
    xdim0_calc_dt_kernel_h = xdim0;
    cudaMemcpyToSymbol(xdim1_calc_dt_kernel, &xdim1, sizeof(int));
    xdim1_calc_dt_kernel_h = xdim1;
    cudaMemcpyToSymbol(xdim2_calc_dt_kernel, &xdim2, sizeof(int));
    xdim2_calc_dt_kernel_h = xdim2;
    cudaMemcpyToSymbol(xdim3_calc_dt_kernel, &xdim3, sizeof(int));
    xdim3_calc_dt_kernel_h = xdim3;
    cudaMemcpyToSymbol(xdim4_calc_dt_kernel, &xdim4, sizeof(int));
    xdim4_calc_dt_kernel_h = xdim4;
    cudaMemcpyToSymbol(xdim5_calc_dt_kernel, &xdim5, sizeof(int));
    xdim5_calc_dt_kernel_h = xdim5;
    cudaMemcpyToSymbol(xdim6_calc_dt_kernel, &xdim6, sizeof(int));
    xdim6_calc_dt_kernel_h = xdim6;
    cudaMemcpyToSymbol(xdim7_calc_dt_kernel, &xdim7, sizeof(int));
    xdim7_calc_dt_kernel_h = xdim7;
    cudaMemcpyToSymbol(xdim8_calc_dt_kernel, &xdim8, sizeof(int));
    xdim8_calc_dt_kernel_h = xdim8;
    cudaMemcpyToSymbol(xdim9_calc_dt_kernel, &xdim9, sizeof(int));
    xdim9_calc_dt_kernel_h = xdim9;
    cudaMemcpyToSymbol(xdim10_calc_dt_kernel, &xdim10, sizeof(int));
    xdim10_calc_dt_kernel_h = xdim10;
  }

  dim3 grid((x_size - 1) / OPS_block_size_x + 1,
            (y_size - 1) / OPS_block_size_y + 1, 1);
  dim3 tblock(OPS_block_size_x, OPS_block_size_y, OPS_block_size_z);

  int dat0 = (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size);
  int dat1 = (OPS_soa ? args[1].dat->type_size : args[1].dat->elem_size);
  int dat2 = (OPS_soa ? args[2].dat->type_size : args[2].dat->elem_size);
  int dat3 = (OPS_soa ? args[3].dat->type_size : args[3].dat->elem_size);
  int dat4 = (OPS_soa ? args[4].dat->type_size : args[4].dat->elem_size);
  int dat5 = (OPS_soa ? args[5].dat->type_size : args[5].dat->elem_size);
  int dat6 = (OPS_soa ? args[6].dat->type_size : args[6].dat->elem_size);
  int dat7 = (OPS_soa ? args[7].dat->type_size : args[7].dat->elem_size);
  int dat8 = (OPS_soa ? args[8].dat->type_size : args[8].dat->elem_size);
  int dat9 = (OPS_soa ? args[9].dat->type_size : args[9].dat->elem_size);
  int dat10 = (OPS_soa ? args[10].dat->type_size : args[10].dat->elem_size);

  char *p_a[11];

  // set up initial pointers
  int base0 = args[0].dat->base_offset +
              dat0 * 1 * (start[0] * args[0].stencil->stride[0]);
  base0 = base0 +
          dat0 * args[0].dat->size[0] * (start[1] * args[0].stencil->stride[1]);
  p_a[0] = (char *)args[0].data_d + base0;

  int base1 = args[1].dat->base_offset +
              dat1 * 1 * (start[0] * args[1].stencil->stride[0]);
  base1 = base1 +
          dat1 * args[1].dat->size[0] * (start[1] * args[1].stencil->stride[1]);
  p_a[1] = (char *)args[1].data_d + base1;

  int base2 = args[2].dat->base_offset +
              dat2 * 1 * (start[0] * args[2].stencil->stride[0]);
  base2 = base2 +
          dat2 * args[2].dat->size[0] * (start[1] * args[2].stencil->stride[1]);
  p_a[2] = (char *)args[2].data_d + base2;

  int base3 = args[3].dat->base_offset +
              dat3 * 1 * (start[0] * args[3].stencil->stride[0]);
  base3 = base3 +
          dat3 * args[3].dat->size[0] * (start[1] * args[3].stencil->stride[1]);
  p_a[3] = (char *)args[3].data_d + base3;

  int base4 = args[4].dat->base_offset +
              dat4 * 1 * (start[0] * args[4].stencil->stride[0]);
  base4 = base4 +
          dat4 * args[4].dat->size[0] * (start[1] * args[4].stencil->stride[1]);
  p_a[4] = (char *)args[4].data_d + base4;

  int base5 = args[5].dat->base_offset +
              dat5 * 1 * (start[0] * args[5].stencil->stride[0]);
  base5 = base5 +
          dat5 * args[5].dat->size[0] * (start[1] * args[5].stencil->stride[1]);
  p_a[5] = (char *)args[5].data_d + base5;

  int base6 = args[6].dat->base_offset +
              dat6 * 1 * (start[0] * args[6].stencil->stride[0]);
  base6 = base6 +
          dat6 * args[6].dat->size[0] * (start[1] * args[6].stencil->stride[1]);
  p_a[6] = (char *)args[6].data_d + base6;

  int base7 = args[7].dat->base_offset +
              dat7 * 1 * (start[0] * args[7].stencil->stride[0]);
  base7 = base7 +
          dat7 * args[7].dat->size[0] * (start[1] * args[7].stencil->stride[1]);
  p_a[7] = (char *)args[7].data_d + base7;

  int base8 = args[8].dat->base_offset +
              dat8 * 1 * (start[0] * args[8].stencil->stride[0]);
  base8 = base8 +
          dat8 * args[8].dat->size[0] * (start[1] * args[8].stencil->stride[1]);
  p_a[8] = (char *)args[8].data_d + base8;

  int base9 = args[9].dat->base_offset +
              dat9 * 1 * (start[0] * args[9].stencil->stride[0]);
  base9 = base9 +
          dat9 * args[9].dat->size[0] * (start[1] * args[9].stencil->stride[1]);
  p_a[9] = (char *)args[9].data_d + base9;

  int base10 = args[10].dat->base_offset +
               dat10 * 1 * (start[0] * args[10].stencil->stride[0]);
  base10 =
      base10 +
      dat10 * args[10].dat->size[0] * (start[1] * args[10].stencil->stride[1]);
  p_a[10] = (char *)args[10].data_d + base10;

#ifndef OPS_LAZY
  ops_H_D_exchanges_device(args, 11);
  ops_halo_exchanges(args, 11, range);
#endif

  if (OPS_diags > 1) {
    ops_timers_core(&c2, &t2);
    OPS_kernels[27].mpi_time += t2 - t1;
  }

  // call kernel wrapper function, passing in pointers to data
  if (x_size > 0 && y_size > 0)
    ops_calc_dt_kernel<<<grid, tblock>>>(
        (double *)p_a[0], (double *)p_a[1], (double *)p_a[2], (double *)p_a[3],
        (double *)p_a[4], (double *)p_a[5], (double *)p_a[6], (double *)p_a[7],
        (double *)p_a[8], (double *)p_a[9], (double *)p_a[10], x_size, y_size);

  cutilSafeCall(cudaGetLastError());

  if (OPS_diags > 1) {
    cutilSafeCall(cudaDeviceSynchronize());
    ops_timers_core(&c1, &t1);
    OPS_kernels[27].time += t1 - t2;
  }

#ifndef OPS_LAZY
  ops_set_dirtybit_device(args, 11);
  ops_set_halo_dirtybit3(&args[10], range);
#endif

  if (OPS_diags > 1) {
    // Update kernel record
    ops_timers_core(&c2, &t2);
    OPS_kernels[27].mpi_time += t2 - t1;
    OPS_kernels[27].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[27].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[27].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_kernels[27].transfer += ops_compute_transfer(dim, start, end, &arg3);
    OPS_kernels[27].transfer += ops_compute_transfer(dim, start, end, &arg4);
    OPS_kernels[27].transfer += ops_compute_transfer(dim, start, end, &arg5);
    OPS_kernels[27].transfer += ops_compute_transfer(dim, start, end, &arg6);
    OPS_kernels[27].transfer += ops_compute_transfer(dim, start, end, &arg7);
    OPS_kernels[27].transfer += ops_compute_transfer(dim, start, end, &arg8);
    OPS_kernels[27].transfer += ops_compute_transfer(dim, start, end, &arg9);
    OPS_kernels[27].transfer += ops_compute_transfer(dim, start, end, &arg10);
  }
}

#ifdef OPS_LAZY
void ops_par_loop_calc_dt_kernel(char const *name, ops_block block, int dim,
                                 int *range, ops_arg arg0, ops_arg arg1,
                                 ops_arg arg2, ops_arg arg3, ops_arg arg4,
                                 ops_arg arg5, ops_arg arg6, ops_arg arg7,
                                 ops_arg arg8, ops_arg arg9, ops_arg arg10) {
  ops_kernel_descriptor *desc =
      (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->device = 1;
  desc->index = 27;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 27;
  for (int i = 0; i < 4; i++) {
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 11;
  desc->args = (ops_arg *)malloc(11 * sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg0.dat->index;
  desc->args[1] = arg1;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg1.dat->index;
  desc->args[2] = arg2;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg2.dat->index;
  desc->args[3] = arg3;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg3.dat->index;
  desc->args[4] = arg4;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg4.dat->index;
  desc->args[5] = arg5;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg5.dat->index;
  desc->args[6] = arg6;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg6.dat->index;
  desc->args[7] = arg7;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg7.dat->index;
  desc->args[8] = arg8;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg8.dat->index;
  desc->args[9] = arg9;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg9.dat->index;
  desc->args[10] = arg10;
  desc->hash = ((desc->hash << 5) + desc->hash) + arg10.dat->index;
  desc->function = ops_par_loop_calc_dt_kernel_execute;
  if (OPS_diags > 1) {
    ops_timing_realloc(27, "calc_dt_kernel");
  }
  ops_enqueue_kernel(desc);
}
#endif
