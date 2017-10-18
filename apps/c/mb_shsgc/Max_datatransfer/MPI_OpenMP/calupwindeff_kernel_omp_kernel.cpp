//
// auto-generated by ops.py
//
#define OPS_ACC_MD0(d, x) ((x)*3 + (d))
#define OPS_ACC_MD1(d, x) ((x)*3 + (d))
#define OPS_ACC_MD2(d, x) ((x)*3 + (d))
#define OPS_ACC_MD3(d, x) ((x)*3 + (d))
#define OPS_ACC_MD4(d, x) ((x)*3 + (d))
#define OPS_ACC_MD5(d, x) ((x)*9 + (d))
#define OPS_ACC_MD6(d, x) ((x)*3 + (d))
#ifdef _OPENMP
#include <omp.h>
#endif

// user function
inline void calupwindeff_kernel(const double *cmp, const double *gt,
                                const double *cf, const double *al,
                                const double *ep2, const double *r,
                                double *eff) {
  double e1 = (cmp[OPS_ACC_MD0(0, 0)] *
                   (gt[OPS_ACC_MD1(0, 0)] + gt[OPS_ACC_MD1(0, 1)]) -
               cf[OPS_ACC_MD2(0, 0)] * al[OPS_ACC_MD3(0, 0)]) *
              ep2[OPS_ACC_MD4(0, 0)];
  double e2 = (cmp[OPS_ACC_MD0(1, 0)] *
                   (gt[OPS_ACC_MD1(1, 0)] + gt[OPS_ACC_MD1(1, 1)]) -
               cf[OPS_ACC_MD2(1, 0)] * al[OPS_ACC_MD3(1, 0)]) *
              ep2[OPS_ACC_MD4(1, 0)];
  double e3 = (cmp[OPS_ACC_MD0(2, 0)] *
                   (gt[OPS_ACC_MD1(2, 0)] + gt[OPS_ACC_MD1(2, 1)]) -
               cf[OPS_ACC_MD2(2, 0)] * al[OPS_ACC_MD3(2, 0)]) *
              ep2[OPS_ACC_MD4(2, 0)];

  eff[OPS_ACC_MD6(0, 0)] = e1 * r[OPS_ACC_MD5(0, 0)] +
                           e2 * r[OPS_ACC_MD5(1, 0)] +
                           e3 * r[OPS_ACC_MD5(2, 0)];
  eff[OPS_ACC_MD6(1, 0)] = e1 * r[OPS_ACC_MD5(3, 0)] +
                           e2 * r[OPS_ACC_MD5(4, 0)] +
                           e3 * r[OPS_ACC_MD5(5, 0)];
  eff[OPS_ACC_MD6(2, 0)] = e1 * r[OPS_ACC_MD5(6, 0)] +
                           e2 * r[OPS_ACC_MD5(7, 0)] +
                           e3 * r[OPS_ACC_MD5(8, 0)];
}

#undef OPS_ACC_MD0
#undef OPS_ACC_MD1
#undef OPS_ACC_MD2
#undef OPS_ACC_MD3
#undef OPS_ACC_MD4
#undef OPS_ACC_MD5
#undef OPS_ACC_MD6

// host stub function
void ops_par_loop_calupwindeff_kernel(char const *name, ops_block block,
                                      int dim, int *range, ops_arg arg0,
                                      ops_arg arg1, ops_arg arg2, ops_arg arg3,
                                      ops_arg arg4, ops_arg arg5,
                                      ops_arg arg6) {

  // Timing
  double t1, t2, c1, c2;

  int offs[7][1];
  ops_arg args[7] = {arg0, arg1, arg2, arg3, arg4, arg5, arg6};

#ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args, 7, range, 11))
    return;
#endif

  if (OPS_diags > 1) {
    ops_timing_realloc(11, "calupwindeff_kernel");
    OPS_kernels[11].count++;
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
  ops_register_args(args, "calupwindeff_kernel");
#endif

  offs[0][0] = args[0].stencil->stride[0] * 1; // unit step in x dimension

  offs[1][0] = args[1].stencil->stride[0] * 1; // unit step in x dimension

  offs[2][0] = args[2].stencil->stride[0] * 1; // unit step in x dimension

  offs[3][0] = args[3].stencil->stride[0] * 1; // unit step in x dimension

  offs[4][0] = args[4].stencil->stride[0] * 1; // unit step in x dimension

  offs[5][0] = args[5].stencil->stride[0] * 1; // unit step in x dimension

  offs[6][0] = args[6].stencil->stride[0] * 1; // unit step in x dimension

  int off0_0 = offs[0][0];
  int dat0 = (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size);
  int off1_0 = offs[1][0];
  int dat1 = (OPS_soa ? args[1].dat->type_size : args[1].dat->elem_size);
  int off2_0 = offs[2][0];
  int dat2 = (OPS_soa ? args[2].dat->type_size : args[2].dat->elem_size);
  int off3_0 = offs[3][0];
  int dat3 = (OPS_soa ? args[3].dat->type_size : args[3].dat->elem_size);
  int off4_0 = offs[4][0];
  int dat4 = (OPS_soa ? args[4].dat->type_size : args[4].dat->elem_size);
  int off5_0 = offs[5][0];
  int dat5 = (OPS_soa ? args[5].dat->type_size : args[5].dat->elem_size);
  int off6_0 = offs[6][0];
  int dat6 = (OPS_soa ? args[6].dat->type_size : args[6].dat->elem_size);

  // Halo Exchanges
  ops_H_D_exchanges_host(args, 7);
  ops_halo_exchanges(args, 7, range);
  ops_H_D_exchanges_host(args, 7);

#ifdef _OPENMP
  int nthreads = omp_get_max_threads();
#else
  int nthreads = 1;
#endif
  xdim0 = args[0].dat->size[0];
  xdim1 = args[1].dat->size[0];
  xdim2 = args[2].dat->size[0];
  xdim3 = args[3].dat->size[0];
  xdim4 = args[4].dat->size[0];
  xdim5 = args[5].dat->size[0];
  xdim6 = args[6].dat->size[0];

  if (OPS_diags > 1) {
    ops_timers_core(&c2, &t2);
    OPS_kernels[11].mpi_time += t2 - t1;
  }

#pragma omp parallel for
  for (int thr = 0; thr < nthreads; thr++) {

    int x_size = end[0] - start[0];
    char *p_a[7];

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

#ifdef OPS_MPI
    for (int d = 0; d < dim; d++)
      d_m[d] =
          args[3].dat->d_m[d] + OPS_sub_dat_list[args[3].dat->index]->d_im[d];
#else
    for (int d = 0; d < dim; d++)
      d_m[d] = args[3].dat->d_m[d];
#endif
    int base3 = dat3 * 1 * (start0 * args[3].stencil->stride[0] -
                            args[3].dat->base[0] - d_m[0]);
    p_a[3] = (char *)args[3].data + base3;

#ifdef OPS_MPI
    for (int d = 0; d < dim; d++)
      d_m[d] =
          args[4].dat->d_m[d] + OPS_sub_dat_list[args[4].dat->index]->d_im[d];
#else
    for (int d = 0; d < dim; d++)
      d_m[d] = args[4].dat->d_m[d];
#endif
    int base4 = dat4 * 1 * (start0 * args[4].stencil->stride[0] -
                            args[4].dat->base[0] - d_m[0]);
    p_a[4] = (char *)args[4].data + base4;

#ifdef OPS_MPI
    for (int d = 0; d < dim; d++)
      d_m[d] =
          args[5].dat->d_m[d] + OPS_sub_dat_list[args[5].dat->index]->d_im[d];
#else
    for (int d = 0; d < dim; d++)
      d_m[d] = args[5].dat->d_m[d];
#endif
    int base5 = dat5 * 1 * (start0 * args[5].stencil->stride[0] -
                            args[5].dat->base[0] - d_m[0]);
    p_a[5] = (char *)args[5].data + base5;

#ifdef OPS_MPI
    for (int d = 0; d < dim; d++)
      d_m[d] =
          args[6].dat->d_m[d] + OPS_sub_dat_list[args[6].dat->index]->d_im[d];
#else
    for (int d = 0; d < dim; d++)
      d_m[d] = args[6].dat->d_m[d];
#endif
    int base6 = dat6 * 1 * (start0 * args[6].stencil->stride[0] -
                            args[6].dat->base[0] - d_m[0]);
    p_a[6] = (char *)args[6].data + base6;

    for (int n_x = start_i; n_x < start_i + (finish_i - start_i) / SIMD_VEC;
         n_x++) {
// call kernel function, passing in pointers to data -vectorised
#pragma simd
      for (int i = 0; i < SIMD_VEC; i++) {
        calupwindeff_kernel((const double *)p_a[0] + i * 1 * 3,
                            (const double *)p_a[1] + i * 1 * 3,
                            (const double *)p_a[2] + i * 1 * 3,
                            (const double *)p_a[3] + i * 1 * 3,
                            (const double *)p_a[4] + i * 1 * 3,
                            (const double *)p_a[5] + i * 1 * 9,
                            (double *)p_a[6] + i * 1 * 3);
      }

      // shift pointers to data x direction
      p_a[0] = p_a[0] + (dat0 * off0_0) * SIMD_VEC;
      p_a[1] = p_a[1] + (dat1 * off1_0) * SIMD_VEC;
      p_a[2] = p_a[2] + (dat2 * off2_0) * SIMD_VEC;
      p_a[3] = p_a[3] + (dat3 * off3_0) * SIMD_VEC;
      p_a[4] = p_a[4] + (dat4 * off4_0) * SIMD_VEC;
      p_a[5] = p_a[5] + (dat5 * off5_0) * SIMD_VEC;
      p_a[6] = p_a[6] + (dat6 * off6_0) * SIMD_VEC;
    }

    for (int n_x = start_i + ((finish_i - start_i) / SIMD_VEC) * SIMD_VEC;
         n_x < finish_i; n_x++) {
      // call kernel function, passing in pointers to data - remainder
      calupwindeff_kernel((const double *)p_a[0], (const double *)p_a[1],
                          (const double *)p_a[2], (const double *)p_a[3],
                          (const double *)p_a[4], (const double *)p_a[5],
                          (double *)p_a[6]);

      // shift pointers to data x direction
      p_a[0] = p_a[0] + (dat0 * off0_0);
      p_a[1] = p_a[1] + (dat1 * off1_0);
      p_a[2] = p_a[2] + (dat2 * off2_0);
      p_a[3] = p_a[3] + (dat3 * off3_0);
      p_a[4] = p_a[4] + (dat4 * off4_0);
      p_a[5] = p_a[5] + (dat5 * off5_0);
      p_a[6] = p_a[6] + (dat6 * off6_0);
    }
  }

  if (OPS_diags > 1) {
    ops_timers_core(&c1, &t1);
    OPS_kernels[11].time += t1 - t2;
  }

  ops_set_dirtybit_host(args, 7);

  ops_set_halo_dirtybit3(&args[6], range);

  if (OPS_diags > 1) {
    // Update kernel record
    ops_timers_core(&c2, &t2);
    OPS_kernels[11].mpi_time += t2 - t1;
    OPS_kernels[11].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[11].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[11].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_kernels[11].transfer += ops_compute_transfer(dim, start, end, &arg3);
    OPS_kernels[11].transfer += ops_compute_transfer(dim, start, end, &arg4);
    OPS_kernels[11].transfer += ops_compute_transfer(dim, start, end, &arg5);
    OPS_kernels[11].transfer += ops_compute_transfer(dim, start, end, &arg6);
  }
}
