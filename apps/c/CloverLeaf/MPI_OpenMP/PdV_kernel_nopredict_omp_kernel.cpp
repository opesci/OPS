//
// auto-generated by ops.py
//
#ifdef _OPENMP
#include <omp.h>
#endif

// user function
inline void PdV_kernel_nopredict(const double *xarea, const double *xvel0,
                                 const double *xvel1, const double *yarea,
                                 const double *yvel0, const double *yvel1,
                                 double *volume_change, const double *volume,
                                 const double *pressure, const double *density0,
                                 double *density1, const double *viscosity,
                                 const double *energy0, double *energy1) {

  double recip_volume, energy_change;
  double right_flux, left_flux, top_flux, bottom_flux, total_flux;

  left_flux = (xarea[OPS_ACC0(0, 0)] *
               (xvel0[OPS_ACC1(0, 0)] + xvel0[OPS_ACC1(0, 1)] +
                xvel1[OPS_ACC2(0, 0)] + xvel1[OPS_ACC2(0, 1)])) *
              0.25 * dt;
  right_flux = (xarea[OPS_ACC0(1, 0)] *
                (xvel0[OPS_ACC1(1, 0)] + xvel0[OPS_ACC1(1, 1)] +
                 xvel1[OPS_ACC2(1, 0)] + xvel1[OPS_ACC2(1, 1)])) *
               0.25 * dt;

  bottom_flux = (yarea[OPS_ACC3(0, 0)] *
                 (yvel0[OPS_ACC4(0, 0)] + yvel0[OPS_ACC4(1, 0)] +
                  yvel1[OPS_ACC5(0, 0)] + yvel1[OPS_ACC5(1, 0)])) *
                0.25 * dt;
  top_flux = (yarea[OPS_ACC3(0, 1)] *
              (yvel0[OPS_ACC4(0, 1)] + yvel0[OPS_ACC4(1, 1)] +
               yvel1[OPS_ACC5(0, 1)] + yvel1[OPS_ACC5(1, 1)])) *
             0.25 * dt;

  total_flux = right_flux - left_flux + top_flux - bottom_flux;

  volume_change[OPS_ACC6(0, 0)] =
      (volume[OPS_ACC7(0, 0)]) / (volume[OPS_ACC7(0, 0)] + total_flux);

  recip_volume = 1.0 / volume[OPS_ACC7(0, 0)];

  energy_change = (pressure[OPS_ACC8(0, 0)] / density0[OPS_ACC9(0, 0)] +
                   viscosity[OPS_ACC11(0, 0)] / density0[OPS_ACC9(0, 0)]) *
                  total_flux * recip_volume;
  energy1[OPS_ACC13(0, 0)] = energy0[OPS_ACC12(0, 0)] - energy_change;
  density1[OPS_ACC10(0, 0)] =
      density0[OPS_ACC9(0, 0)] * volume_change[OPS_ACC6(0, 0)];
}

// host stub function
void ops_par_loop_PdV_kernel_nopredict(char const *name, ops_block block,
                                       int dim, int *range, ops_arg arg0,
                                       ops_arg arg1, ops_arg arg2, ops_arg arg3,
                                       ops_arg arg4, ops_arg arg5, ops_arg arg6,
                                       ops_arg arg7, ops_arg arg8, ops_arg arg9,
                                       ops_arg arg10, ops_arg arg11,
                                       ops_arg arg12, ops_arg arg13) {

  // Timing
  double t1, t2, c1, c2;

  int offs[14][2];
  ops_arg args[14] = {arg0, arg1, arg2, arg3,  arg4,  arg5,  arg6,
                      arg7, arg8, arg9, arg10, arg11, arg12, arg13};

#ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args, 14, range, 5))
    return;
#endif

  if (OPS_diags > 1) {
    ops_timing_realloc(5, "PdV_kernel_nopredict");
    OPS_kernels[5].count++;
    ops_timers_core(&c1, &t1);
  }

  // compute locally allocated range for the sub-block

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
#ifdef OPS_DEBUG
  ops_register_args(args, "PdV_kernel_nopredict");
#endif

  offs[0][0] = args[0].stencil->stride[0] * 1; // unit step in x dimension
  offs[0][1] =
      off2D(1, &start[0], &end[0], args[0].dat->size, args[0].stencil->stride) -
      offs[0][0];

  offs[1][0] = args[1].stencil->stride[0] * 1; // unit step in x dimension
  offs[1][1] =
      off2D(1, &start[0], &end[0], args[1].dat->size, args[1].stencil->stride) -
      offs[1][0];

  offs[2][0] = args[2].stencil->stride[0] * 1; // unit step in x dimension
  offs[2][1] =
      off2D(1, &start[0], &end[0], args[2].dat->size, args[2].stencil->stride) -
      offs[2][0];

  offs[3][0] = args[3].stencil->stride[0] * 1; // unit step in x dimension
  offs[3][1] =
      off2D(1, &start[0], &end[0], args[3].dat->size, args[3].stencil->stride) -
      offs[3][0];

  offs[4][0] = args[4].stencil->stride[0] * 1; // unit step in x dimension
  offs[4][1] =
      off2D(1, &start[0], &end[0], args[4].dat->size, args[4].stencil->stride) -
      offs[4][0];

  offs[5][0] = args[5].stencil->stride[0] * 1; // unit step in x dimension
  offs[5][1] =
      off2D(1, &start[0], &end[0], args[5].dat->size, args[5].stencil->stride) -
      offs[5][0];

  offs[6][0] = args[6].stencil->stride[0] * 1; // unit step in x dimension
  offs[6][1] =
      off2D(1, &start[0], &end[0], args[6].dat->size, args[6].stencil->stride) -
      offs[6][0];

  offs[7][0] = args[7].stencil->stride[0] * 1; // unit step in x dimension
  offs[7][1] =
      off2D(1, &start[0], &end[0], args[7].dat->size, args[7].stencil->stride) -
      offs[7][0];

  offs[8][0] = args[8].stencil->stride[0] * 1; // unit step in x dimension
  offs[8][1] =
      off2D(1, &start[0], &end[0], args[8].dat->size, args[8].stencil->stride) -
      offs[8][0];

  offs[9][0] = args[9].stencil->stride[0] * 1; // unit step in x dimension
  offs[9][1] =
      off2D(1, &start[0], &end[0], args[9].dat->size, args[9].stencil->stride) -
      offs[9][0];

  offs[10][0] = args[10].stencil->stride[0] * 1; // unit step in x dimension
  offs[10][1] = off2D(1, &start[0], &end[0], args[10].dat->size,
                      args[10].stencil->stride) -
                offs[10][0];

  offs[11][0] = args[11].stencil->stride[0] * 1; // unit step in x dimension
  offs[11][1] = off2D(1, &start[0], &end[0], args[11].dat->size,
                      args[11].stencil->stride) -
                offs[11][0];

  offs[12][0] = args[12].stencil->stride[0] * 1; // unit step in x dimension
  offs[12][1] = off2D(1, &start[0], &end[0], args[12].dat->size,
                      args[12].stencil->stride) -
                offs[12][0];

  offs[13][0] = args[13].stencil->stride[0] * 1; // unit step in x dimension
  offs[13][1] = off2D(1, &start[0], &end[0], args[13].dat->size,
                      args[13].stencil->stride) -
                offs[13][0];

  int off0_0 = offs[0][0];
  int off0_1 = offs[0][1];
  int dat0 = (OPS_soa ? args[0].dat->type_size : args[0].dat->elem_size);
  int off1_0 = offs[1][0];
  int off1_1 = offs[1][1];
  int dat1 = (OPS_soa ? args[1].dat->type_size : args[1].dat->elem_size);
  int off2_0 = offs[2][0];
  int off2_1 = offs[2][1];
  int dat2 = (OPS_soa ? args[2].dat->type_size : args[2].dat->elem_size);
  int off3_0 = offs[3][0];
  int off3_1 = offs[3][1];
  int dat3 = (OPS_soa ? args[3].dat->type_size : args[3].dat->elem_size);
  int off4_0 = offs[4][0];
  int off4_1 = offs[4][1];
  int dat4 = (OPS_soa ? args[4].dat->type_size : args[4].dat->elem_size);
  int off5_0 = offs[5][0];
  int off5_1 = offs[5][1];
  int dat5 = (OPS_soa ? args[5].dat->type_size : args[5].dat->elem_size);
  int off6_0 = offs[6][0];
  int off6_1 = offs[6][1];
  int dat6 = (OPS_soa ? args[6].dat->type_size : args[6].dat->elem_size);
  int off7_0 = offs[7][0];
  int off7_1 = offs[7][1];
  int dat7 = (OPS_soa ? args[7].dat->type_size : args[7].dat->elem_size);
  int off8_0 = offs[8][0];
  int off8_1 = offs[8][1];
  int dat8 = (OPS_soa ? args[8].dat->type_size : args[8].dat->elem_size);
  int off9_0 = offs[9][0];
  int off9_1 = offs[9][1];
  int dat9 = (OPS_soa ? args[9].dat->type_size : args[9].dat->elem_size);
  int off10_0 = offs[10][0];
  int off10_1 = offs[10][1];
  int dat10 = (OPS_soa ? args[10].dat->type_size : args[10].dat->elem_size);
  int off11_0 = offs[11][0];
  int off11_1 = offs[11][1];
  int dat11 = (OPS_soa ? args[11].dat->type_size : args[11].dat->elem_size);
  int off12_0 = offs[12][0];
  int off12_1 = offs[12][1];
  int dat12 = (OPS_soa ? args[12].dat->type_size : args[12].dat->elem_size);
  int off13_0 = offs[13][0];
  int off13_1 = offs[13][1];
  int dat13 = (OPS_soa ? args[13].dat->type_size : args[13].dat->elem_size);

  // Halo Exchanges
  ops_H_D_exchanges_host(args, 14);
  ops_halo_exchanges(args, 14, range);
  ops_H_D_exchanges_host(args, 14);

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
  xdim7 = args[7].dat->size[0];
  xdim8 = args[8].dat->size[0];
  xdim9 = args[9].dat->size[0];
  xdim10 = args[10].dat->size[0];
  xdim11 = args[11].dat->size[0];
  xdim12 = args[12].dat->size[0];
  xdim13 = args[13].dat->size[0];

  if (OPS_diags > 1) {
    ops_timers_core(&c2, &t2);
    OPS_kernels[5].mpi_time += t2 - t1;
  }

#pragma omp parallel for
  for (int thr = 0; thr < nthreads; thr++) {

    int y_size = end[1] - start[1];
    char *p_a[14];

    int start_i = start[1] + ((y_size - 1) / nthreads + 1) * thr;
    int finish_i =
        start[1] + MIN(((y_size - 1) / nthreads + 1) * (thr + 1), y_size);

    // get address per thread
    int start0 = start[0];
    int start1 = start_i;

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
    base0 = base0 +
            dat0 * args[0].dat->size[0] * (start1 * args[0].stencil->stride[1] -
                                           args[0].dat->base[1] - d_m[1]);
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
    base1 = base1 +
            dat1 * args[1].dat->size[0] * (start1 * args[1].stencil->stride[1] -
                                           args[1].dat->base[1] - d_m[1]);
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
    base2 = base2 +
            dat2 * args[2].dat->size[0] * (start1 * args[2].stencil->stride[1] -
                                           args[2].dat->base[1] - d_m[1]);
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
    base3 = base3 +
            dat3 * args[3].dat->size[0] * (start1 * args[3].stencil->stride[1] -
                                           args[3].dat->base[1] - d_m[1]);
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
    base4 = base4 +
            dat4 * args[4].dat->size[0] * (start1 * args[4].stencil->stride[1] -
                                           args[4].dat->base[1] - d_m[1]);
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
    base5 = base5 +
            dat5 * args[5].dat->size[0] * (start1 * args[5].stencil->stride[1] -
                                           args[5].dat->base[1] - d_m[1]);
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
    base6 = base6 +
            dat6 * args[6].dat->size[0] * (start1 * args[6].stencil->stride[1] -
                                           args[6].dat->base[1] - d_m[1]);
    p_a[6] = (char *)args[6].data + base6;

#ifdef OPS_MPI
    for (int d = 0; d < dim; d++)
      d_m[d] =
          args[7].dat->d_m[d] + OPS_sub_dat_list[args[7].dat->index]->d_im[d];
#else
    for (int d = 0; d < dim; d++)
      d_m[d] = args[7].dat->d_m[d];
#endif
    int base7 = dat7 * 1 * (start0 * args[7].stencil->stride[0] -
                            args[7].dat->base[0] - d_m[0]);
    base7 = base7 +
            dat7 * args[7].dat->size[0] * (start1 * args[7].stencil->stride[1] -
                                           args[7].dat->base[1] - d_m[1]);
    p_a[7] = (char *)args[7].data + base7;

#ifdef OPS_MPI
    for (int d = 0; d < dim; d++)
      d_m[d] =
          args[8].dat->d_m[d] + OPS_sub_dat_list[args[8].dat->index]->d_im[d];
#else
    for (int d = 0; d < dim; d++)
      d_m[d] = args[8].dat->d_m[d];
#endif
    int base8 = dat8 * 1 * (start0 * args[8].stencil->stride[0] -
                            args[8].dat->base[0] - d_m[0]);
    base8 = base8 +
            dat8 * args[8].dat->size[0] * (start1 * args[8].stencil->stride[1] -
                                           args[8].dat->base[1] - d_m[1]);
    p_a[8] = (char *)args[8].data + base8;

#ifdef OPS_MPI
    for (int d = 0; d < dim; d++)
      d_m[d] =
          args[9].dat->d_m[d] + OPS_sub_dat_list[args[9].dat->index]->d_im[d];
#else
    for (int d = 0; d < dim; d++)
      d_m[d] = args[9].dat->d_m[d];
#endif
    int base9 = dat9 * 1 * (start0 * args[9].stencil->stride[0] -
                            args[9].dat->base[0] - d_m[0]);
    base9 = base9 +
            dat9 * args[9].dat->size[0] * (start1 * args[9].stencil->stride[1] -
                                           args[9].dat->base[1] - d_m[1]);
    p_a[9] = (char *)args[9].data + base9;

#ifdef OPS_MPI
    for (int d = 0; d < dim; d++)
      d_m[d] =
          args[10].dat->d_m[d] + OPS_sub_dat_list[args[10].dat->index]->d_im[d];
#else
    for (int d = 0; d < dim; d++)
      d_m[d] = args[10].dat->d_m[d];
#endif
    int base10 = dat10 * 1 * (start0 * args[10].stencil->stride[0] -
                              args[10].dat->base[0] - d_m[0]);
    base10 =
        base10 +
        dat10 * args[10].dat->size[0] * (start1 * args[10].stencil->stride[1] -
                                         args[10].dat->base[1] - d_m[1]);
    p_a[10] = (char *)args[10].data + base10;

#ifdef OPS_MPI
    for (int d = 0; d < dim; d++)
      d_m[d] =
          args[11].dat->d_m[d] + OPS_sub_dat_list[args[11].dat->index]->d_im[d];
#else
    for (int d = 0; d < dim; d++)
      d_m[d] = args[11].dat->d_m[d];
#endif
    int base11 = dat11 * 1 * (start0 * args[11].stencil->stride[0] -
                              args[11].dat->base[0] - d_m[0]);
    base11 =
        base11 +
        dat11 * args[11].dat->size[0] * (start1 * args[11].stencil->stride[1] -
                                         args[11].dat->base[1] - d_m[1]);
    p_a[11] = (char *)args[11].data + base11;

#ifdef OPS_MPI
    for (int d = 0; d < dim; d++)
      d_m[d] =
          args[12].dat->d_m[d] + OPS_sub_dat_list[args[12].dat->index]->d_im[d];
#else
    for (int d = 0; d < dim; d++)
      d_m[d] = args[12].dat->d_m[d];
#endif
    int base12 = dat12 * 1 * (start0 * args[12].stencil->stride[0] -
                              args[12].dat->base[0] - d_m[0]);
    base12 =
        base12 +
        dat12 * args[12].dat->size[0] * (start1 * args[12].stencil->stride[1] -
                                         args[12].dat->base[1] - d_m[1]);
    p_a[12] = (char *)args[12].data + base12;

#ifdef OPS_MPI
    for (int d = 0; d < dim; d++)
      d_m[d] =
          args[13].dat->d_m[d] + OPS_sub_dat_list[args[13].dat->index]->d_im[d];
#else
    for (int d = 0; d < dim; d++)
      d_m[d] = args[13].dat->d_m[d];
#endif
    int base13 = dat13 * 1 * (start0 * args[13].stencil->stride[0] -
                              args[13].dat->base[0] - d_m[0]);
    base13 =
        base13 +
        dat13 * args[13].dat->size[0] * (start1 * args[13].stencil->stride[1] -
                                         args[13].dat->base[1] - d_m[1]);
    p_a[13] = (char *)args[13].data + base13;

    for (int n_y = start_i; n_y < finish_i; n_y++) {
      for (int n_x = start[0]; n_x < start[0] + (end[0] - start[0]) / SIMD_VEC;
           n_x++) {
// call kernel function, passing in pointers to data -vectorised
#pragma simd
        for (int i = 0; i < SIMD_VEC; i++) {
          PdV_kernel_nopredict(
              (const double *)p_a[0] + i * 1 * 1,
              (const double *)p_a[1] + i * 1 * 1,
              (const double *)p_a[2] + i * 1 * 1,
              (const double *)p_a[3] + i * 1 * 1,
              (const double *)p_a[4] + i * 1 * 1,
              (const double *)p_a[5] + i * 1 * 1, (double *)p_a[6] + i * 1 * 1,
              (const double *)p_a[7] + i * 1 * 1,
              (const double *)p_a[8] + i * 1 * 1,
              (const double *)p_a[9] + i * 1 * 1, (double *)p_a[10] + i * 1 * 1,
              (const double *)p_a[11] + i * 1 * 1,
              (const double *)p_a[12] + i * 1 * 1,
              (double *)p_a[13] + i * 1 * 1);
        }

        // shift pointers to data x direction
        p_a[0] = p_a[0] + (dat0 * off0_0) * SIMD_VEC;
        p_a[1] = p_a[1] + (dat1 * off1_0) * SIMD_VEC;
        p_a[2] = p_a[2] + (dat2 * off2_0) * SIMD_VEC;
        p_a[3] = p_a[3] + (dat3 * off3_0) * SIMD_VEC;
        p_a[4] = p_a[4] + (dat4 * off4_0) * SIMD_VEC;
        p_a[5] = p_a[5] + (dat5 * off5_0) * SIMD_VEC;
        p_a[6] = p_a[6] + (dat6 * off6_0) * SIMD_VEC;
        p_a[7] = p_a[7] + (dat7 * off7_0) * SIMD_VEC;
        p_a[8] = p_a[8] + (dat8 * off8_0) * SIMD_VEC;
        p_a[9] = p_a[9] + (dat9 * off9_0) * SIMD_VEC;
        p_a[10] = p_a[10] + (dat10 * off10_0) * SIMD_VEC;
        p_a[11] = p_a[11] + (dat11 * off11_0) * SIMD_VEC;
        p_a[12] = p_a[12] + (dat12 * off12_0) * SIMD_VEC;
        p_a[13] = p_a[13] + (dat13 * off13_0) * SIMD_VEC;
      }

      for (int n_x = start[0] + ((end[0] - start[0]) / SIMD_VEC) * SIMD_VEC;
           n_x < end[0]; n_x++) {
        // call kernel function, passing in pointers to data - remainder
        PdV_kernel_nopredict((const double *)p_a[0], (const double *)p_a[1],
                             (const double *)p_a[2], (const double *)p_a[3],
                             (const double *)p_a[4], (const double *)p_a[5],
                             (double *)p_a[6], (const double *)p_a[7],
                             (const double *)p_a[8], (const double *)p_a[9],
                             (double *)p_a[10], (const double *)p_a[11],
                             (const double *)p_a[12], (double *)p_a[13]);

        // shift pointers to data x direction
        p_a[0] = p_a[0] + (dat0 * off0_0);
        p_a[1] = p_a[1] + (dat1 * off1_0);
        p_a[2] = p_a[2] + (dat2 * off2_0);
        p_a[3] = p_a[3] + (dat3 * off3_0);
        p_a[4] = p_a[4] + (dat4 * off4_0);
        p_a[5] = p_a[5] + (dat5 * off5_0);
        p_a[6] = p_a[6] + (dat6 * off6_0);
        p_a[7] = p_a[7] + (dat7 * off7_0);
        p_a[8] = p_a[8] + (dat8 * off8_0);
        p_a[9] = p_a[9] + (dat9 * off9_0);
        p_a[10] = p_a[10] + (dat10 * off10_0);
        p_a[11] = p_a[11] + (dat11 * off11_0);
        p_a[12] = p_a[12] + (dat12 * off12_0);
        p_a[13] = p_a[13] + (dat13 * off13_0);
      }

      // shift pointers to data y direction
      p_a[0] = p_a[0] + (dat0 * off0_1);
      p_a[1] = p_a[1] + (dat1 * off1_1);
      p_a[2] = p_a[2] + (dat2 * off2_1);
      p_a[3] = p_a[3] + (dat3 * off3_1);
      p_a[4] = p_a[4] + (dat4 * off4_1);
      p_a[5] = p_a[5] + (dat5 * off5_1);
      p_a[6] = p_a[6] + (dat6 * off6_1);
      p_a[7] = p_a[7] + (dat7 * off7_1);
      p_a[8] = p_a[8] + (dat8 * off8_1);
      p_a[9] = p_a[9] + (dat9 * off9_1);
      p_a[10] = p_a[10] + (dat10 * off10_1);
      p_a[11] = p_a[11] + (dat11 * off11_1);
      p_a[12] = p_a[12] + (dat12 * off12_1);
      p_a[13] = p_a[13] + (dat13 * off13_1);
    }
  }

  if (OPS_diags > 1) {
    ops_timers_core(&c1, &t1);
    OPS_kernels[5].time += t1 - t2;
  }

  ops_set_dirtybit_host(args, 14);

  ops_set_halo_dirtybit3(&args[6], range);
  ops_set_halo_dirtybit3(&args[10], range);
  ops_set_halo_dirtybit3(&args[13], range);

  if (OPS_diags > 1) {
    // Update kernel record
    ops_timers_core(&c2, &t2);
    OPS_kernels[5].mpi_time += t2 - t1;
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg3);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg4);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg5);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg6);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg7);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg8);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg9);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg10);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg11);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg12);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, start, end, &arg13);
  }
}
