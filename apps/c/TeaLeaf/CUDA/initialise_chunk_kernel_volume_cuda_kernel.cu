//
// auto-generated by ops.py
//
__constant__ int xdim0_initialise_chunk_kernel_volume;
int xdim0_initialise_chunk_kernel_volume_h = -1;
__constant__ int xdim1_initialise_chunk_kernel_volume;
int xdim1_initialise_chunk_kernel_volume_h = -1;
__constant__ int xdim2_initialise_chunk_kernel_volume;
int xdim2_initialise_chunk_kernel_volume_h = -1;
__constant__ int xdim3_initialise_chunk_kernel_volume;
int xdim3_initialise_chunk_kernel_volume_h = -1;
__constant__ int xdim4_initialise_chunk_kernel_volume;
int xdim4_initialise_chunk_kernel_volume_h = -1;

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4

#define OPS_ACC0(x, y) (x + xdim0_initialise_chunk_kernel_volume * (y))
#define OPS_ACC1(x, y) (x + xdim1_initialise_chunk_kernel_volume * (y))
#define OPS_ACC2(x, y) (x + xdim2_initialise_chunk_kernel_volume * (y))
#define OPS_ACC3(x, y) (x + xdim3_initialise_chunk_kernel_volume * (y))
#define OPS_ACC4(x, y) (x + xdim4_initialise_chunk_kernel_volume * (y))

// user function
__device__

    void
    initialise_chunk_kernel_volume_gpu(double *volume, const double *celldy,
                                       double *xarea, const double *celldx,
                                       double *yarea) {

  double d_x, d_y;

  d_x = (grid.xmax - grid.xmin) / (double)grid.x_cells;
  d_y = (grid.ymax - grid.ymin) / (double)grid.y_cells;

  volume[OPS_ACC0(0, 0)] = d_x * d_y;
  xarea[OPS_ACC2(0, 0)] = celldy[OPS_ACC1(0, 0)];
  yarea[OPS_ACC4(0, 0)] = celldx[OPS_ACC3(0, 0)];
}

#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4

__global__ void ops_initialise_chunk_kernel_volume(
    double *__restrict arg0, const double *__restrict arg1,
    double *__restrict arg2, const double *__restrict arg3,
    double *__restrict arg4, int size0, int size1) {

  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 * 1 + idx_y * 1 * 1 * xdim0_initialise_chunk_kernel_volume;
  arg1 += idx_x * 0 * 1 + idx_y * 1 * 1 * xdim1_initialise_chunk_kernel_volume;
  arg2 += idx_x * 1 * 1 + idx_y * 1 * 1 * xdim2_initialise_chunk_kernel_volume;
  arg3 += idx_x * 1 * 1 + idx_y * 0 * 1 * xdim3_initialise_chunk_kernel_volume;
  arg4 += idx_x * 1 * 1 + idx_y * 1 * 1 * xdim4_initialise_chunk_kernel_volume;

  if (idx_x < size0 && idx_y < size1) {
    initialise_chunk_kernel_volume_gpu(arg0, arg1, arg2, arg3, arg4);
  }
}

// host stub function
#ifndef OPS_LAZY
void ops_par_loop_initialise_chunk_kernel_volume(char const *name,
                                                 ops_block block, int dim,
                                                 int *range, ops_arg arg0,
                                                 ops_arg arg1, ops_arg arg2,
                                                 ops_arg arg3, ops_arg arg4) {
#else
void ops_par_loop_initialise_chunk_kernel_volume_execute(
    ops_kernel_descriptor *desc) {
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  ops_arg arg2 = desc->args[2];
  ops_arg arg3 = desc->args[3];
  ops_arg arg4 = desc->args[4];
#endif

  // Timing
  double t1, t2, c1, c2;

  ops_arg args[5] = {arg0, arg1, arg2, arg3, arg4};

#if CHECKPOINTING && !OPS_LAZY
  if (!ops_checkpointing_before(args, 5, range, 14))
    return;
#endif

  if (OPS_diags > 1) {
    ops_timing_realloc(14, "initialise_chunk_kernel_volume");
    OPS_kernels[14].count++;
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

  if (xdim0 != xdim0_initialise_chunk_kernel_volume_h ||
      xdim1 != xdim1_initialise_chunk_kernel_volume_h ||
      xdim2 != xdim2_initialise_chunk_kernel_volume_h ||
      xdim3 != xdim3_initialise_chunk_kernel_volume_h ||
      xdim4 != xdim4_initialise_chunk_kernel_volume_h) {
    cudaMemcpyToSymbol(xdim0_initialise_chunk_kernel_volume, &xdim0,
                       sizeof(int));
    xdim0_initialise_chunk_kernel_volume_h = xdim0;
    cudaMemcpyToSymbol(xdim1_initialise_chunk_kernel_volume, &xdim1,
                       sizeof(int));
    xdim1_initialise_chunk_kernel_volume_h = xdim1;
    cudaMemcpyToSymbol(xdim2_initialise_chunk_kernel_volume, &xdim2,
                       sizeof(int));
    xdim2_initialise_chunk_kernel_volume_h = xdim2;
    cudaMemcpyToSymbol(xdim3_initialise_chunk_kernel_volume, &xdim3,
                       sizeof(int));
    xdim3_initialise_chunk_kernel_volume_h = xdim3;
    cudaMemcpyToSymbol(xdim4_initialise_chunk_kernel_volume, &xdim4,
                       sizeof(int));
    xdim4_initialise_chunk_kernel_volume_h = xdim4;
  }

  dim3 grid((x_size - 1) / OPS_block_size_x + 1,
            (y_size - 1) / OPS_block_size_y + 1, 1);
  dim3 tblock(OPS_block_size_x, OPS_block_size_y, 1);

  int dat0 = (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size);
  int dat1 = (OPS_soa ? args[1].dat->type_size : args[1].dat->elem_size);
  int dat2 = (OPS_soa ? args[2].dat->type_size : args[2].dat->elem_size);
  int dat3 = (OPS_soa ? args[3].dat->type_size : args[3].dat->elem_size);
  int dat4 = (OPS_soa ? args[4].dat->type_size : args[4].dat->elem_size);

  char *p_a[5];

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

#ifndef OPS_LAZY
  ops_H_D_exchanges_device(args, 5);
  ops_halo_exchanges(args, 5, range);
#endif

  if (OPS_diags > 1) {
    ops_timers_core(&c2, &t2);
    OPS_kernels[14].mpi_time += t2 - t1;
  }

  // call kernel wrapper function, passing in pointers to data
  ops_initialise_chunk_kernel_volume<<<grid, tblock>>>(
      (double *)p_a[0], (double *)p_a[1], (double *)p_a[2], (double *)p_a[3],
      (double *)p_a[4], x_size, y_size);

  if (OPS_diags > 1) {
    cutilSafeCall(cudaDeviceSynchronize());
    ops_timers_core(&c1, &t1);
    OPS_kernels[14].time += t1 - t2;
  }

#ifndef OPS_LAZY
  ops_set_dirtybit_device(args, 5);
  ops_set_halo_dirtybit3(&args[0], range);
  ops_set_halo_dirtybit3(&args[2], range);
  ops_set_halo_dirtybit3(&args[4], range);
#endif

  if (OPS_diags > 1) {
    // Update kernel record
    ops_timers_core(&c2, &t2);
    OPS_kernels[14].mpi_time += t2 - t1;
    OPS_kernels[14].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[14].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[14].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_kernels[14].transfer += ops_compute_transfer(dim, start, end, &arg3);
    OPS_kernels[14].transfer += ops_compute_transfer(dim, start, end, &arg4);
  }
}

#ifdef OPS_LAZY
void ops_par_loop_initialise_chunk_kernel_volume(char const *name,
                                                 ops_block block, int dim,
                                                 int *range, ops_arg arg0,
                                                 ops_arg arg1, ops_arg arg2,
                                                 ops_arg arg3, ops_arg arg4) {
  ops_kernel_descriptor *desc =
      (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->device = 1;
  desc->index = 14;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 14;
  for (int i = 0; i < 4; i++) {
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 5;
  desc->args = (ops_arg *)malloc(5 * sizeof(ops_arg));
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
  desc->function = ops_par_loop_initialise_chunk_kernel_volume_execute;
  if (OPS_diags > 1) {
    ops_timing_realloc(14, "initialise_chunk_kernel_volume");
  }
  ops_enqueue_kernel(desc);
}
#endif