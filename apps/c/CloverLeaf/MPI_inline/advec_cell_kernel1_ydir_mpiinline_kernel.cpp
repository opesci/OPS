//
// auto-generated by ops.py
//

extern int xdim0_advec_cell_kernel1_ydir;
int xdim0_advec_cell_kernel1_ydir_h = -1;
extern int xdim1_advec_cell_kernel1_ydir;
int xdim1_advec_cell_kernel1_ydir_h = -1;
extern int xdim2_advec_cell_kernel1_ydir;
int xdim2_advec_cell_kernel1_ydir_h = -1;
extern int xdim3_advec_cell_kernel1_ydir;
int xdim3_advec_cell_kernel1_ydir_h = -1;
extern int xdim4_advec_cell_kernel1_ydir;
int xdim4_advec_cell_kernel1_ydir_h = -1;

#ifdef __cplusplus
extern "C" {
#endif
void advec_cell_kernel1_ydir_c_wrapper(double *p_a0, double *p_a1, double *p_a2,
                                       double *p_a3, double *p_a4, int x_size,
                                       int y_size);

#ifdef __cplusplus
}
#endif

// host stub function
void ops_par_loop_advec_cell_kernel1_ydir(char const *name, ops_block block,
                                          int dim, int *range, ops_arg arg0,
                                          ops_arg arg1, ops_arg arg2,
                                          ops_arg arg3, ops_arg arg4) {

  ops_arg args[5] = {arg0, arg1, arg2, arg3, arg4};

#ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args, 5, range, 11))
    return;
#endif

  ops_timing_realloc(11, "advec_cell_kernel1_ydir");
  OPS_kernels[11].count++;

  // compute localy allocated range for the sub-block
  int start[2];
  int end[2];
#ifdef OPS_MPI
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

  xdim0 = args[0].dat->size[0];
  xdim1 = args[1].dat->size[0];
  xdim2 = args[2].dat->size[0];
  xdim3 = args[3].dat->size[0];
  xdim4 = args[4].dat->size[0];

  // Timing
  double t1, t2, c1, c2;
  ops_timers_core(&c2, &t2);

  if (xdim0 != xdim0_advec_cell_kernel1_ydir_h ||
      xdim1 != xdim1_advec_cell_kernel1_ydir_h ||
      xdim2 != xdim2_advec_cell_kernel1_ydir_h ||
      xdim3 != xdim3_advec_cell_kernel1_ydir_h ||
      xdim4 != xdim4_advec_cell_kernel1_ydir_h) {
    xdim0_advec_cell_kernel1_ydir = xdim0;
    xdim0_advec_cell_kernel1_ydir_h = xdim0;
    xdim1_advec_cell_kernel1_ydir = xdim1;
    xdim1_advec_cell_kernel1_ydir_h = xdim1;
    xdim2_advec_cell_kernel1_ydir = xdim2;
    xdim2_advec_cell_kernel1_ydir_h = xdim2;
    xdim3_advec_cell_kernel1_ydir = xdim3;
    xdim3_advec_cell_kernel1_ydir_h = xdim3;
    xdim4_advec_cell_kernel1_ydir = xdim4;
    xdim4_advec_cell_kernel1_ydir_h = xdim4;
  }

  int dat0 = (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size);
  int dat1 = (OPS_soa ? args[1].dat->type_size : args[1].dat->elem_size);
  int dat2 = (OPS_soa ? args[2].dat->type_size : args[2].dat->elem_size);
  int dat3 = (OPS_soa ? args[3].dat->type_size : args[3].dat->elem_size);
  int dat4 = (OPS_soa ? args[4].dat->type_size : args[4].dat->elem_size);

  // set up initial pointers
  int d_m[OPS_MAX_DIM];
#ifdef OPS_MPI
  for (int d = 0; d < dim; d++)
    d_m[d] =
        args[0].dat->d_m[d] + OPS_sub_dat_list[args[0].dat->index]->d_im[d];
#else
  for (int d = 0; d < dim; d++)
    d_m[d] = args[0].dat->d_m[d];
#endif
  int base0 = dat0 * 1 * (start[0] * args[0].stencil->stride[0] -
                          args[0].dat->base[0] - d_m[0]);
  base0 = base0 +
          dat0 * args[0].dat->size[0] * (start[1] * args[0].stencil->stride[1] -
                                         args[0].dat->base[1] - d_m[1]);
  double *p_a0 = (double *)((char *)args[0].data + base0);

#ifdef OPS_MPI
  for (int d = 0; d < dim; d++)
    d_m[d] =
        args[1].dat->d_m[d] + OPS_sub_dat_list[args[1].dat->index]->d_im[d];
#else
  for (int d = 0; d < dim; d++)
    d_m[d] = args[1].dat->d_m[d];
#endif
  int base1 = dat1 * 1 * (start[0] * args[1].stencil->stride[0] -
                          args[1].dat->base[0] - d_m[0]);
  base1 = base1 +
          dat1 * args[1].dat->size[0] * (start[1] * args[1].stencil->stride[1] -
                                         args[1].dat->base[1] - d_m[1]);
  double *p_a1 = (double *)((char *)args[1].data + base1);

#ifdef OPS_MPI
  for (int d = 0; d < dim; d++)
    d_m[d] =
        args[2].dat->d_m[d] + OPS_sub_dat_list[args[2].dat->index]->d_im[d];
#else
  for (int d = 0; d < dim; d++)
    d_m[d] = args[2].dat->d_m[d];
#endif
  int base2 = dat2 * 1 * (start[0] * args[2].stencil->stride[0] -
                          args[2].dat->base[0] - d_m[0]);
  base2 = base2 +
          dat2 * args[2].dat->size[0] * (start[1] * args[2].stencil->stride[1] -
                                         args[2].dat->base[1] - d_m[1]);
  double *p_a2 = (double *)((char *)args[2].data + base2);

#ifdef OPS_MPI
  for (int d = 0; d < dim; d++)
    d_m[d] =
        args[3].dat->d_m[d] + OPS_sub_dat_list[args[3].dat->index]->d_im[d];
#else
  for (int d = 0; d < dim; d++)
    d_m[d] = args[3].dat->d_m[d];
#endif
  int base3 = dat3 * 1 * (start[0] * args[3].stencil->stride[0] -
                          args[3].dat->base[0] - d_m[0]);
  base3 = base3 +
          dat3 * args[3].dat->size[0] * (start[1] * args[3].stencil->stride[1] -
                                         args[3].dat->base[1] - d_m[1]);
  double *p_a3 = (double *)((char *)args[3].data + base3);

#ifdef OPS_MPI
  for (int d = 0; d < dim; d++)
    d_m[d] =
        args[4].dat->d_m[d] + OPS_sub_dat_list[args[4].dat->index]->d_im[d];
#else
  for (int d = 0; d < dim; d++)
    d_m[d] = args[4].dat->d_m[d];
#endif
  int base4 = dat4 * 1 * (start[0] * args[4].stencil->stride[0] -
                          args[4].dat->base[0] - d_m[0]);
  base4 = base4 +
          dat4 * args[4].dat->size[0] * (start[1] * args[4].stencil->stride[1] -
                                         args[4].dat->base[1] - d_m[1]);
  double *p_a4 = (double *)((char *)args[4].data + base4);

  ops_H_D_exchanges_host(args, 5);
  ops_halo_exchanges(args, 5, range);

  ops_timers_core(&c1, &t1);
  OPS_kernels[11].mpi_time += t1 - t2;

  advec_cell_kernel1_ydir_c_wrapper(p_a0, p_a1, p_a2, p_a3, p_a4, x_size,
                                    y_size);

  ops_timers_core(&c2, &t2);
  OPS_kernels[11].time += t2 - t1;
  ops_set_dirtybit_host(args, 5);
  ops_set_halo_dirtybit3(&args[0], range);
  ops_set_halo_dirtybit3(&args[1], range);

  // Update kernel record
  OPS_kernels[11].transfer += ops_compute_transfer(dim, start, end, &arg0);
  OPS_kernels[11].transfer += ops_compute_transfer(dim, start, end, &arg1);
  OPS_kernels[11].transfer += ops_compute_transfer(dim, start, end, &arg2);
  OPS_kernels[11].transfer += ops_compute_transfer(dim, start, end, &arg3);
  OPS_kernels[11].transfer += ops_compute_transfer(dim, start, end, &arg4);
}
