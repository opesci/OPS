//
// auto-generated by ops.py
//
#define OPS_ACC_MD0(d,x,y) ((x)*2+(d)+(xdim0*(y)*2))

//user function
inline void multidim_reduce_kernel(const double *val, double *redu_dat1) {

  redu_dat1[0] = redu_dat1[0] + val[OPS_ACC_MD0(0,0,0)];
  redu_dat1[1] = redu_dat1[1] + val[OPS_ACC_MD0(1,0,0)];
}



#undef OPS_ACC_MD0


// host stub function
void ops_par_loop_multidim_reduce_kernel(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1) {

  //Timing
  double t1,t2,c1,c2;

  char *p_a[2];
  int  offs[2][2];
  ops_arg args[2] = { arg0, arg1};



  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,2,range,2)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(2,"multidim_reduce_kernel");
    OPS_kernels[2].count++;
    ops_timers_core(&c2,&t2);
  }

  //compute locally allocated range for the sub-block
  int start[2];
  int end[2];

  #ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned) return;
  for ( int n=0; n<2; n++ ){
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
  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #endif //OPS_MPI
  #ifdef OPS_DEBUG
  ops_register_args(args, "multidim_reduce_kernel");
  #endif

  offs[0][0] = args[0].stencil->stride[0]*1;  //unit step in x dimension
  offs[0][1] = off2D(1, &start[0],
      &end[0],args[0].dat->size, args[0].stencil->stride) - offs[0][0];



  int off0_0 = offs[0][0];
  int off0_1 = offs[0][1];
  int dat0 = args[0].dat->elem_size;

  //set up initial pointers and exchange halos if necessary
  int d_m[OPS_MAX_DIM];
  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d] + OPS_sub_dat_list[args[0].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[0].dat->d_m[d];
  #endif //OPS_MPI
  int base0 = dat0 * 1 *
    (start[0] * args[0].stencil->stride[0] - args[0].dat->base[0] - d_m[0]);
  base0 = base0+ dat0 *
    args[0].dat->size[0] *
    (start[1] * args[0].stencil->stride[1] - args[0].dat->base[1] - d_m[1]);
  p_a[0] = (char *)args[0].data + base0;

  #ifdef OPS_MPI
  p_a[1] = ((ops_reduction)args[1].data)->data + ((ops_reduction)args[1].data)->size * block->index;
  #else //OPS_MPI
  p_a[1] = ((ops_reduction)args[1].data)->data;
  #endif //OPS_MPI



  //initialize global variable with the dimension of dats
  xdim0 = args[0].dat->size[0];

  //Halo Exchanges
  ops_H_D_exchanges_host(args, 2);
  ops_halo_exchanges(args,2,range);
  ops_H_D_exchanges_host(args, 2);

  if (OPS_diags > 1) {
    ops_timers_core(&c1,&t1);
    OPS_kernels[2].mpi_time += t1-t2;
  }

  int n_x;
  for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
    #pragma novector
    for( n_x=start[0]; n_x<start[0]+((end[0]-start[0])/SIMD_VEC)*SIMD_VEC; n_x+=SIMD_VEC ) {
      //call kernel function, passing in pointers to data -vectorised
      for ( int i=0; i<SIMD_VEC; i++ ){
        multidim_reduce_kernel(  (double *)p_a[0]+ i*1*2, (double *)p_a[1] );

      }

      //shift pointers to data x direction
      p_a[0]= p_a[0] + (dat0 * off0_0)*SIMD_VEC;
    }

    for ( int n_x=start[0]+((end[0]-start[0])/SIMD_VEC)*SIMD_VEC; n_x<end[0]; n_x++ ){
      //call kernel function, passing in pointers to data - remainder
      multidim_reduce_kernel(  (double *)p_a[0], (double *)p_a[1] );


      //shift pointers to data x direction
      p_a[0]= p_a[0] + (dat0 * off0_0);
    }

    //shift pointers to data y direction
    p_a[0]= p_a[0] + (dat0 * off0_1);
  }
  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[2].time += t2-t1;
  }
  ops_set_dirtybit_host(args, 2);

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c1,&t1);
    OPS_kernels[2].mpi_time += t1-t2;
    OPS_kernels[2].transfer += ops_compute_transfer(dim, range, &arg0);
  }
}
