//
// auto-generated by ops.py
//
#ifdef _OPENMP
#include <omp.h>
#endif

//user function

inline void update_halo_kernel1_l1(double *density0, double *density1,
                          double *energy0, double *energy1,
                          double *pressure, double *viscosity,
                          double *soundspeed , const int* fields) {
  if(fields[FIELD_DENSITY0] == 1) density0[OPS_ACC0(0,0,0)] = density0[OPS_ACC0(1,0,0)];
  if(fields[FIELD_DENSITY1] == 1) density1[OPS_ACC1(0,0,0)] = density1[OPS_ACC1(1,0,0)];
  if(fields[FIELD_ENERGY0] == 1) energy0[OPS_ACC2(0,0,0)] = energy0[OPS_ACC2(1,0,0)];
  if(fields[FIELD_ENERGY1] == 1) energy1[OPS_ACC3(0,0,0)] = energy1[OPS_ACC3(1,0,0)];
  if(fields[FIELD_PRESSURE] == 1) pressure[OPS_ACC4(0,0,0)] = pressure[OPS_ACC4(1,0,0)];
  if(fields[FIELD_VISCOSITY] == 1) viscosity[OPS_ACC5(0,0,0)] = viscosity[OPS_ACC5(1,0,0)];
  if(fields[FIELD_SOUNDSPEED] == 1) soundspeed[OPS_ACC6(0,0,0)] = soundspeed[OPS_ACC6(1,0,0)];

}



// host stub function
void ops_par_loop_update_halo_kernel1_l1(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7) {

  //Timing
  double t1,t2,c1,c2;
  ops_timers_core(&c1,&t1);


  int  offs[8][3];
  ops_arg args[8] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7};



  ops_timing_realloc(46,"update_halo_kernel1_l1");
  OPS_kernels[46].count++;

  //compute locally allocated range for the sub-block

  int start[3];
  int end[3];

  #ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned) return;
  for ( int n=0; n<3; n++ ){
    start[n] = sb->decomp_disp[n];end[n] = sb->decomp_disp[n]+sb->decomp_size[n];
    if (start[n] >= range[2*n]) {
      start[n] = 0;
    }
    else {
      start[n] = range[2*n] - start[n];
    }
    if (sb->id_m[n]==MPI_PROC_NULL && range[2*n] < 0) start[n] = range[2*n];
    if (end[n] >= range[2*n+1]) {
      end[n] = range[2*n+1] - sb->decomp_disp[n];
    }
    else {
      end[n] = sb->decomp_size[n];
    }
    if (sb->id_p[n]==MPI_PROC_NULL && (range[2*n+1] > sb->decomp_disp[n]+sb->decomp_size[n]))
      end[n] += (range[2*n+1]-sb->decomp_disp[n]-sb->decomp_size[n]);
  }
  #else //OPS_MPI
  for ( int n=0; n<3; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #endif //OPS_MPI
  #ifdef OPS_DEBUG
  ops_register_args(args, "update_halo_kernel1_l1");
  #endif

  offs[0][0] = args[0].stencil->stride[0]*1;  //unit step in x dimension
  offs[0][1] = off3D(1, &start[0],
      &end[0],args[0].dat->size, args[0].stencil->stride) - offs[0][0];
  offs[0][2] = off3D(2, &start[0],
      &end[0],args[0].dat->size, args[0].stencil->stride) - offs[0][1] - offs[0][0];

  offs[1][0] = args[1].stencil->stride[0]*1;  //unit step in x dimension
  offs[1][1] = off3D(1, &start[0],
      &end[0],args[1].dat->size, args[1].stencil->stride) - offs[1][0];
  offs[1][2] = off3D(2, &start[0],
      &end[0],args[1].dat->size, args[1].stencil->stride) - offs[1][1] - offs[1][0];

  offs[2][0] = args[2].stencil->stride[0]*1;  //unit step in x dimension
  offs[2][1] = off3D(1, &start[0],
      &end[0],args[2].dat->size, args[2].stencil->stride) - offs[2][0];
  offs[2][2] = off3D(2, &start[0],
      &end[0],args[2].dat->size, args[2].stencil->stride) - offs[2][1] - offs[2][0];

  offs[3][0] = args[3].stencil->stride[0]*1;  //unit step in x dimension
  offs[3][1] = off3D(1, &start[0],
      &end[0],args[3].dat->size, args[3].stencil->stride) - offs[3][0];
  offs[3][2] = off3D(2, &start[0],
      &end[0],args[3].dat->size, args[3].stencil->stride) - offs[3][1] - offs[3][0];

  offs[4][0] = args[4].stencil->stride[0]*1;  //unit step in x dimension
  offs[4][1] = off3D(1, &start[0],
      &end[0],args[4].dat->size, args[4].stencil->stride) - offs[4][0];
  offs[4][2] = off3D(2, &start[0],
      &end[0],args[4].dat->size, args[4].stencil->stride) - offs[4][1] - offs[4][0];

  offs[5][0] = args[5].stencil->stride[0]*1;  //unit step in x dimension
  offs[5][1] = off3D(1, &start[0],
      &end[0],args[5].dat->size, args[5].stencil->stride) - offs[5][0];
  offs[5][2] = off3D(2, &start[0],
      &end[0],args[5].dat->size, args[5].stencil->stride) - offs[5][1] - offs[5][0];

  offs[6][0] = args[6].stencil->stride[0]*1;  //unit step in x dimension
  offs[6][1] = off3D(1, &start[0],
      &end[0],args[6].dat->size, args[6].stencil->stride) - offs[6][0];
  offs[6][2] = off3D(2, &start[0],
      &end[0],args[6].dat->size, args[6].stencil->stride) - offs[6][1] - offs[6][0];



  int off0_0 = offs[0][0];
  int off0_1 = offs[0][1];
  int off0_2 = offs[0][2];
  int dat0 = args[0].dat->elem_size;
  int off1_0 = offs[1][0];
  int off1_1 = offs[1][1];
  int off1_2 = offs[1][2];
  int dat1 = args[1].dat->elem_size;
  int off2_0 = offs[2][0];
  int off2_1 = offs[2][1];
  int off2_2 = offs[2][2];
  int dat2 = args[2].dat->elem_size;
  int off3_0 = offs[3][0];
  int off3_1 = offs[3][1];
  int off3_2 = offs[3][2];
  int dat3 = args[3].dat->elem_size;
  int off4_0 = offs[4][0];
  int off4_1 = offs[4][1];
  int off4_2 = offs[4][2];
  int dat4 = args[4].dat->elem_size;
  int off5_0 = offs[5][0];
  int off5_1 = offs[5][1];
  int off5_2 = offs[5][2];
  int dat5 = args[5].dat->elem_size;
  int off6_0 = offs[6][0];
  int off6_1 = offs[6][1];
  int off6_2 = offs[6][2];
  int dat6 = args[6].dat->elem_size;


  #ifdef _OPENMP
  int nthreads = omp_get_max_threads( );
  #else
  int nthreads = 1;
  #endif
  xdim0 = args[0].dat->size[0]*args[0].dat->dim;
  ydim0 = args[0].dat->size[1];
  xdim1 = args[1].dat->size[0]*args[1].dat->dim;
  ydim1 = args[1].dat->size[1];
  xdim2 = args[2].dat->size[0]*args[2].dat->dim;
  ydim2 = args[2].dat->size[1];
  xdim3 = args[3].dat->size[0]*args[3].dat->dim;
  ydim3 = args[3].dat->size[1];
  xdim4 = args[4].dat->size[0]*args[4].dat->dim;
  ydim4 = args[4].dat->size[1];
  xdim5 = args[5].dat->size[0]*args[5].dat->dim;
  ydim5 = args[5].dat->size[1];
  xdim6 = args[6].dat->size[0]*args[6].dat->dim;
  ydim6 = args[6].dat->size[1];

  ops_H_D_exchanges_host(args, 8);

  //Halo Exchanges
  ops_halo_exchanges(args,8,range);


  ops_timers_core(&c2,&t2);
  OPS_kernels[46].mpi_time += t2-t1;


  #pragma omp parallel for
  for ( int thr=0; thr<nthreads; thr++ ){

    int z_size = end[2]-start[2];
    char *p_a[8];

    int start_i = start[2] + ((z_size-1)/nthreads+1)*thr;
    int finish_i = start[2] + MIN(((z_size-1)/nthreads+1)*(thr+1),z_size);

    //get address per thread
    int start0 = start[0];
    int start1 = start[1];
    int start2 = start_i;

    //set up initial pointers 
    int d_m[OPS_MAX_DIM];
    #ifdef OPS_MPI
    for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d] + OPS_sub_dat_list[args[0].dat->index]->d_im[d];
    #else //OPS_MPI
    for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d];
    #endif //OPS_MPI
    int base0 = dat0 * 1 * 
    (start0 * args[0].stencil->stride[0] - args[0].dat->base[0] - d_m[0]);
    base0 = base0+ dat0 *
      args[0].dat->size[0] *
      (start1 * args[0].stencil->stride[1] - args[0].dat->base[1] - d_m[1]);
    base0 = base0+ dat0 *
      args[0].dat->size[0] *
      args[0].dat->size[1] *
      (start2 * args[0].stencil->stride[2] - args[0].dat->base[2] - d_m[2]);
    p_a[0] = (char *)args[0].data + base0;

    #ifdef OPS_MPI
    for (int d = 0; d < dim; d++) d_m[d] = args[1].dat->d_m[d] + OPS_sub_dat_list[args[1].dat->index]->d_im[d];
    #else //OPS_MPI
    for (int d = 0; d < dim; d++) d_m[d] = args[1].dat->d_m[d];
    #endif //OPS_MPI
    int base1 = dat1 * 1 * 
    (start0 * args[1].stencil->stride[0] - args[1].dat->base[0] - d_m[0]);
    base1 = base1+ dat1 *
      args[1].dat->size[0] *
      (start1 * args[1].stencil->stride[1] - args[1].dat->base[1] - d_m[1]);
    base1 = base1+ dat1 *
      args[1].dat->size[0] *
      args[1].dat->size[1] *
      (start2 * args[1].stencil->stride[2] - args[1].dat->base[2] - d_m[2]);
    p_a[1] = (char *)args[1].data + base1;

    #ifdef OPS_MPI
    for (int d = 0; d < dim; d++) d_m[d] = args[2].dat->d_m[d] + OPS_sub_dat_list[args[2].dat->index]->d_im[d];
    #else //OPS_MPI
    for (int d = 0; d < dim; d++) d_m[d] = args[2].dat->d_m[d];
    #endif //OPS_MPI
    int base2 = dat2 * 1 * 
    (start0 * args[2].stencil->stride[0] - args[2].dat->base[0] - d_m[0]);
    base2 = base2+ dat2 *
      args[2].dat->size[0] *
      (start1 * args[2].stencil->stride[1] - args[2].dat->base[1] - d_m[1]);
    base2 = base2+ dat2 *
      args[2].dat->size[0] *
      args[2].dat->size[1] *
      (start2 * args[2].stencil->stride[2] - args[2].dat->base[2] - d_m[2]);
    p_a[2] = (char *)args[2].data + base2;

    #ifdef OPS_MPI
    for (int d = 0; d < dim; d++) d_m[d] = args[3].dat->d_m[d] + OPS_sub_dat_list[args[3].dat->index]->d_im[d];
    #else //OPS_MPI
    for (int d = 0; d < dim; d++) d_m[d] = args[3].dat->d_m[d];
    #endif //OPS_MPI
    int base3 = dat3 * 1 * 
    (start0 * args[3].stencil->stride[0] - args[3].dat->base[0] - d_m[0]);
    base3 = base3+ dat3 *
      args[3].dat->size[0] *
      (start1 * args[3].stencil->stride[1] - args[3].dat->base[1] - d_m[1]);
    base3 = base3+ dat3 *
      args[3].dat->size[0] *
      args[3].dat->size[1] *
      (start2 * args[3].stencil->stride[2] - args[3].dat->base[2] - d_m[2]);
    p_a[3] = (char *)args[3].data + base3;

    #ifdef OPS_MPI
    for (int d = 0; d < dim; d++) d_m[d] = args[4].dat->d_m[d] + OPS_sub_dat_list[args[4].dat->index]->d_im[d];
    #else //OPS_MPI
    for (int d = 0; d < dim; d++) d_m[d] = args[4].dat->d_m[d];
    #endif //OPS_MPI
    int base4 = dat4 * 1 * 
    (start0 * args[4].stencil->stride[0] - args[4].dat->base[0] - d_m[0]);
    base4 = base4+ dat4 *
      args[4].dat->size[0] *
      (start1 * args[4].stencil->stride[1] - args[4].dat->base[1] - d_m[1]);
    base4 = base4+ dat4 *
      args[4].dat->size[0] *
      args[4].dat->size[1] *
      (start2 * args[4].stencil->stride[2] - args[4].dat->base[2] - d_m[2]);
    p_a[4] = (char *)args[4].data + base4;

    #ifdef OPS_MPI
    for (int d = 0; d < dim; d++) d_m[d] = args[5].dat->d_m[d] + OPS_sub_dat_list[args[5].dat->index]->d_im[d];
    #else //OPS_MPI
    for (int d = 0; d < dim; d++) d_m[d] = args[5].dat->d_m[d];
    #endif //OPS_MPI
    int base5 = dat5 * 1 * 
    (start0 * args[5].stencil->stride[0] - args[5].dat->base[0] - d_m[0]);
    base5 = base5+ dat5 *
      args[5].dat->size[0] *
      (start1 * args[5].stencil->stride[1] - args[5].dat->base[1] - d_m[1]);
    base5 = base5+ dat5 *
      args[5].dat->size[0] *
      args[5].dat->size[1] *
      (start2 * args[5].stencil->stride[2] - args[5].dat->base[2] - d_m[2]);
    p_a[5] = (char *)args[5].data + base5;

    #ifdef OPS_MPI
    for (int d = 0; d < dim; d++) d_m[d] = args[6].dat->d_m[d] + OPS_sub_dat_list[args[6].dat->index]->d_im[d];
    #else //OPS_MPI
    for (int d = 0; d < dim; d++) d_m[d] = args[6].dat->d_m[d];
    #endif //OPS_MPI
    int base6 = dat6 * 1 * 
    (start0 * args[6].stencil->stride[0] - args[6].dat->base[0] - d_m[0]);
    base6 = base6+ dat6 *
      args[6].dat->size[0] *
      (start1 * args[6].stencil->stride[1] - args[6].dat->base[1] - d_m[1]);
    base6 = base6+ dat6 *
      args[6].dat->size[0] *
      args[6].dat->size[1] *
      (start2 * args[6].stencil->stride[2] - args[6].dat->base[2] - d_m[2]);
    p_a[6] = (char *)args[6].data + base6;

    p_a[7] = (char *)args[7].data;


    for ( int n_z=start_i; n_z<finish_i; n_z++ ){
      for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
        for ( int n_x=start[0]; n_x<start[0]+(end[0]-start[0])/SIMD_VEC; n_x++ ){
          //call kernel function, passing in pointers to data -vectorised
          #pragma simd
          for ( int i=0; i<SIMD_VEC; i++ ){
            update_halo_kernel1_l1(  (double * )p_a[0]+ i*1, (double * )p_a[1]+ i*1, (double * )p_a[2]+ i*1,
           (double * )p_a[3]+ i*1, (double * )p_a[4]+ i*1, (double * )p_a[5]+ i*1, (double * )p_a[6]+ i*1,
           (int * )p_a[7] );

          }

          //shift pointers to data x direction
          p_a[0]= p_a[0] + (dat0 * off0_0)*SIMD_VEC;
          p_a[1]= p_a[1] + (dat1 * off1_0)*SIMD_VEC;
          p_a[2]= p_a[2] + (dat2 * off2_0)*SIMD_VEC;
          p_a[3]= p_a[3] + (dat3 * off3_0)*SIMD_VEC;
          p_a[4]= p_a[4] + (dat4 * off4_0)*SIMD_VEC;
          p_a[5]= p_a[5] + (dat5 * off5_0)*SIMD_VEC;
          p_a[6]= p_a[6] + (dat6 * off6_0)*SIMD_VEC;
        }

        for ( int n_x=start[0]+((end[0]-start[0])/SIMD_VEC)*SIMD_VEC; n_x<end[0]; n_x++ ){
          //call kernel function, passing in pointers to data - remainder
          update_halo_kernel1_l1(  (double * )p_a[0], (double * )p_a[1], (double * )p_a[2],
           (double * )p_a[3], (double * )p_a[4], (double * )p_a[5], (double * )p_a[6],
           (int * )p_a[7] );


          //shift pointers to data x direction
          p_a[0]= p_a[0] + (dat0 * off0_0);
          p_a[1]= p_a[1] + (dat1 * off1_0);
          p_a[2]= p_a[2] + (dat2 * off2_0);
          p_a[3]= p_a[3] + (dat3 * off3_0);
          p_a[4]= p_a[4] + (dat4 * off4_0);
          p_a[5]= p_a[5] + (dat5 * off5_0);
          p_a[6]= p_a[6] + (dat6 * off6_0);
        }

        //shift pointers to data y direction
        p_a[0]= p_a[0] + (dat0 * off0_1);
        p_a[1]= p_a[1] + (dat1 * off1_1);
        p_a[2]= p_a[2] + (dat2 * off2_1);
        p_a[3]= p_a[3] + (dat3 * off3_1);
        p_a[4]= p_a[4] + (dat4 * off4_1);
        p_a[5]= p_a[5] + (dat5 * off5_1);
        p_a[6]= p_a[6] + (dat6 * off6_1);
      }
      //shift pointers to data z direction
      p_a[0]= p_a[0] + (dat0 * off0_2);
      p_a[1]= p_a[1] + (dat1 * off1_2);
      p_a[2]= p_a[2] + (dat2 * off2_2);
      p_a[3]= p_a[3] + (dat3 * off3_2);
      p_a[4]= p_a[4] + (dat4 * off4_2);
      p_a[5]= p_a[5] + (dat5 * off5_2);
      p_a[6]= p_a[6] + (dat6 * off6_2);
    }
  }

  ops_timers_core(&c1,&t1);
  OPS_kernels[46].time += t1-t2;

  ops_set_dirtybit_host(args, 8);

  ops_set_halo_dirtybit3(&args[0],range);
  ops_set_halo_dirtybit3(&args[1],range);
  ops_set_halo_dirtybit3(&args[2],range);
  ops_set_halo_dirtybit3(&args[3],range);
  ops_set_halo_dirtybit3(&args[4],range);
  ops_set_halo_dirtybit3(&args[5],range);
  ops_set_halo_dirtybit3(&args[6],range);

  //Update kernel record
  ops_timers_core(&c2,&t2);
  OPS_kernels[46].mpi_time += t2-t1;
  OPS_kernels[46].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[46].transfer += ops_compute_transfer(dim, range, &arg1);
  OPS_kernels[46].transfer += ops_compute_transfer(dim, range, &arg2);
  OPS_kernels[46].transfer += ops_compute_transfer(dim, range, &arg3);
  OPS_kernels[46].transfer += ops_compute_transfer(dim, range, &arg4);
  OPS_kernels[46].transfer += ops_compute_transfer(dim, range, &arg5);
  OPS_kernels[46].transfer += ops_compute_transfer(dim, range, &arg6);
}
