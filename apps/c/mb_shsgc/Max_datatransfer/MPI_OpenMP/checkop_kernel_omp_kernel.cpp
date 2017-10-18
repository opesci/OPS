//
// auto-generated by ops.py
//
#ifdef _OPENMP
#include <omp.h>
#endif

// user function
inline void checkop_kernel(const double *rho_new, const double *x,
                           const double *rhoin, double *pre, double *post,
                           int *num) {

  double diff;
  diff = (rho_new[OPS_ACC0(0)] - rhoin[OPS_ACC2(0)]);
  if (fabs(diff) < 0.01 && x[OPS_ACC1(0)] > -4.1) {
    *post = *post + diff * diff;
    *num = *num + 1;

  } else
    *pre = *pre + (rho_new[OPS_ACC0(0)] - rhol) * (rho_new[OPS_ACC0(0)] - rhol);
}

// host stub function
void ops_par_loop_checkop_kernel(char const *name, ops_block block, int dim,
                                 int *range, ops_arg arg0, ops_arg arg1,
                                 ops_arg arg2, ops_arg arg3, ops_arg arg4,
                                 ops_arg arg5) {

  // Timing
  double t1, t2, c1, c2;

  int offs[6][1];
  ops_arg args[6] = {arg0, arg1, arg2, arg3, arg4, arg5};

#ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args, 6, range, 14))
    return;
#endif

  if (OPS_diags > 1) {
    ops_timing_realloc(14, "checkop_kernel");
    OPS_kernels[14].count++;
    ops_timers_core(&c1, &t1);
  }

  // compute locally allocated range for the sub-block

  int start[1];
  int end[1];

#ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned)
    return;
  for (int n = 0; n < 1; n++) {
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
  for (int n = 0; n < 1; n++) {
    start[n] = range[2 * n];
    end[n] = range[2 * n + 1];
  }
#endif
#ifdef OPS_DEBUG
  ops_register_args(args, "checkop_kernel");
#endif

  offs[0][0] = args[0].stencil->stride[0] * 1; // unit step in x dimension

  offs[1][0] = args[1].stencil->stride[0] * 1; // unit step in x dimension

  offs[2][0] = args[2].stencil->stride[0] * 1; // unit step in x dimension

  int off0_0 = offs[0][0];
  int dat0 = (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size);
  int off1_0 = offs[1][0];
  int dat1 = (OPS_soa ? args[1].dat->type_size : args[1].dat->elem_size);
  int off2_0 = offs[2][0];
  int dat2 = (OPS_soa ? args[2].dat->type_size : args[2].dat->elem_size);

#ifdef OPS_MPI
  double *arg3h =
      (double *)(((ops_reduction)args[3].data)->data +
                 ((ops_reduction)args[3].data)->size * block->index);
#else
  double *arg3h = (double *)(((ops_reduction)args[3].data)->data);
#endif
#ifdef OPS_MPI
  double *arg4h =
      (double *)(((ops_reduction)args[4].data)->data +
                 ((ops_reduction)args[4].data)->size * block->index);
#else
  double *arg4h = (double *)(((ops_reduction)args[4].data)->data);
#endif
#ifdef OPS_MPI
  int *arg5h = (int *)(((ops_reduction)args[5].data)->data +
                       ((ops_reduction)args[5].data)->size * block->index);
#else
  int *arg5h = (int *)(((ops_reduction)args[5].data)->data);
#endif
  // Halo Exchanges
  ops_H_D_exchanges_host(args, 6);
  ops_halo_exchanges(args, 6, range);
  ops_H_D_exchanges_host(args, 6);

#ifdef _OPENMP
  int nthreads = omp_get_max_threads();
#else
  int nthreads = 1;
#endif
  // allocate and initialise arrays for global reduction
  // assumes a max of MAX_REDUCT_THREADS threads with a cacche line size of 64
  // bytes
  double arg_gbl3[MAX(1, 64) * MAX_REDUCT_THREADS];
  double arg_gbl4[MAX(1, 64) * MAX_REDUCT_THREADS];
  int arg_gbl5[MAX(1, 64) * MAX_REDUCT_THREADS];
  for (int thr = 0; thr < nthreads; thr++) {
    for (int d = 0; d < 1; d++) {
      arg_gbl3[d + 64 * thr] = ZERO_double;
    }
    for (int d = 0; d < 1; d++) {
      arg_gbl4[d + 64 * thr] = ZERO_double;
    }
    for (int d = 0; d < 1; d++) {
      arg_gbl5[d + 64 * thr] = ZERO_int;
    }
  }
  xdim0 = args[0].dat->size[0];
  xdim1 = args[1].dat->size[0];
  xdim2 = args[2].dat->size[0];

  if (OPS_diags > 1) {
    ops_timers_core(&c2, &t2);
    OPS_kernels[14].mpi_time += t2 - t1;
  }

#pragma omp parallel for
  for (int thr = 0; thr < nthreads; thr++) {

    int x_size = end[0] - start[0];
    char *p_a[6];

    int start_i = start[0] + ((x_size - 1) / nthreads + 1) * thr;
    int finish_i =
        start[0] + MIN(((x_size - 1) / nthreads + 1) * (thr + 1), x_size);

    // get address per thread
    int start0 = start_i;

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
    int base0 = dat0 * 1 * (start0 * args[0].stencil->stride[0] -
                            args[0].dat->base[0] - d_m[0]);
    p_a[0] = (char *)args[0].data + base0;

#ifdef OPS_MPI
    for (int d = 0; d < dim; d++)
      d_m[d] =
          args[1].dat->d_m[d] + OPS_sub_dat_list[args[1].dat->index]->d_im[d];
#else
    for (int d = 0; d < dim; d++)
      d_m[d] = args[1].dat->d_m[d];
#endif
    int base1 = dat1 * 1 * (start0 * args[1].stencil->stride[0] -
                            args[1].dat->base[0] - d_m[0]);
    p_a[1] = (char *)args[1].data + base1;

#ifdef OPS_MPI
    for (int d = 0; d < dim; d++)
      d_m[d] =
          args[2].dat->d_m[d] + OPS_sub_dat_list[args[2].dat->index]->d_im[d];
#else
    for (int d = 0; d < dim; d++)
      d_m[d] = args[2].dat->d_m[d];
#endif
    int base2 = dat2 * 1 * (start0 * args[2].stencil->stride[0] -
                            args[2].dat->base[0] - d_m[0]);
    p_a[2] = (char *)args[2].data + base2;

    p_a[3] = (char *)arg3h;

    p_a[4] = (char *)arg4h;

    p_a[5] = (char *)arg5h;

    for (int n_x = start_i; n_x < start_i + (finish_i - start_i) / SIMD_VEC;
         n_x++) {
      // call kernel function, passing in pointers to data -vectorised
      for (int i = 0; i < SIMD_VEC; i++) {
        checkop_kernel((const double *)p_a[0] + i * 1 * 1,
                       (const double *)p_a[1] + i * 1 * 1,
                       (const double *)p_a[2] + i * 1 * 1, &arg_gbl3[64 * thr],
                       &arg_gbl4[64 * thr], &arg_gbl5[64 * thr]);
      }

      // shift pointers to data x direction
      p_a[0] = p_a[0] + (dat0 * off0_0) * SIMD_VEC;
      p_a[1] = p_a[1] + (dat1 * off1_0) * SIMD_VEC;
      p_a[2] = p_a[2] + (dat2 * off2_0) * SIMD_VEC;
    }

    for (int n_x = start_i + ((finish_i - start_i) / SIMD_VEC) * SIMD_VEC;
         n_x < finish_i; n_x++) {
      // call kernel function, passing in pointers to data - remainder
      checkop_kernel((const double *)p_a[0], (const double *)p_a[1],
                     (const double *)p_a[2], &arg_gbl3[64 * thr],
                     &arg_gbl4[64 * thr], &arg_gbl5[64 * thr]);

      // shift pointers to data x direction
      p_a[0] = p_a[0] + (dat0 * off0_0);
      p_a[1] = p_a[1] + (dat1 * off1_0);
      p_a[2] = p_a[2] + (dat2 * off2_0);
    }
  }

  if (OPS_diags > 1) {
    ops_timers_core(&c1, &t1);
    OPS_kernels[14].time += t1 - t2;
  }

  // combine reduction data
  for (int thr = 0; thr < nthreads; thr++) {
    for (int d = 0; d < 1; d++) {
      arg3h[d] += arg_gbl3[64 * thr + d];
    }
    for (int d = 0; d < 1; d++) {
      arg4h[d] += arg_gbl4[64 * thr + d];
    }
    for (int d = 0; d < 1; d++) {
      arg5h[d] += arg_gbl5[64 * thr + d];
    }
  }
  ops_set_dirtybit_host(args, 6);

  if (OPS_diags > 1) {
    // Update kernel record
    ops_timers_core(&c2, &t2);
    OPS_kernels[14].mpi_time += t2 - t1;
    OPS_kernels[14].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[14].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[14].transfer += ops_compute_transfer(dim, start, end, &arg2);
  }
}
