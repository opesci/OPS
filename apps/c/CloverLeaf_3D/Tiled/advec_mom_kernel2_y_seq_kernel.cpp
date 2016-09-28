//
// auto-generated by ops.py
//
#define OPS_ACC0(x,y,z) (n_x*1+n_y*xdim0_advec_mom_kernel2_y*1+n_z*xdim0_advec_mom_kernel2_y*ydim0_advec_mom_kernel2_y*1+x+xdim0_advec_mom_kernel2_y*(y)+xdim0_advec_mom_kernel2_y*ydim0_advec_mom_kernel2_y*(z))
#define OPS_ACC1(x,y,z) (n_x*1+n_y*xdim1_advec_mom_kernel2_y*1+n_z*xdim1_advec_mom_kernel2_y*ydim1_advec_mom_kernel2_y*1+x+xdim1_advec_mom_kernel2_y*(y)+xdim1_advec_mom_kernel2_y*ydim1_advec_mom_kernel2_y*(z))
#define OPS_ACC2(x,y,z) (n_x*1+n_y*xdim2_advec_mom_kernel2_y*1+n_z*xdim2_advec_mom_kernel2_y*ydim2_advec_mom_kernel2_y*1+x+xdim2_advec_mom_kernel2_y*(y)+xdim2_advec_mom_kernel2_y*ydim2_advec_mom_kernel2_y*(z))
#define OPS_ACC3(x,y,z) (n_x*1+n_y*xdim3_advec_mom_kernel2_y*1+n_z*xdim3_advec_mom_kernel2_y*ydim3_advec_mom_kernel2_y*1+x+xdim3_advec_mom_kernel2_y*(y)+xdim3_advec_mom_kernel2_y*ydim3_advec_mom_kernel2_y*(z))


//user function

// host stub function
void ops_par_loop_advec_mom_kernel2_y_execute(ops_kernel_descriptor *desc) {
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  ops_arg arg2 = desc->args[2];
  ops_arg arg3 = desc->args[3];

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[4] = { arg0, arg1, arg2, arg3};



  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,4,range,32)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(32,"advec_mom_kernel2_y");
    OPS_kernels[32].count++;
    ops_timers_core(&c2,&t2);
  }

  //compute locally allocated range for the sub-block
  int start[3];
  int end[3];

  for ( int n=0; n<3; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "advec_mom_kernel2_y");
  #endif



  //set up initial pointers and exchange halos if necessary
  int base0 = args[0].dat->base_offset;
  double * __restrict__ vel1 = (double *)(args[0].data + base0);

  int base1 = args[1].dat->base_offset;
  const double * __restrict__ node_mass_post = (double *)(args[1].data + base1);

  int base2 = args[2].dat->base_offset;
  const double * __restrict__ node_mass_pre = (double *)(args[2].data + base2);

  int base3 = args[3].dat->base_offset;
  const double * __restrict__ mom_flux = (double *)(args[3].data + base3);


  //initialize global variable with the dimension of dats
  int xdim0_advec_mom_kernel2_y = args[0].dat->size[0];
  int ydim0_advec_mom_kernel2_y = args[0].dat->size[1];
  int xdim1_advec_mom_kernel2_y = args[1].dat->size[0];
  int ydim1_advec_mom_kernel2_y = args[1].dat->size[1];
  int xdim2_advec_mom_kernel2_y = args[2].dat->size[0];
  int ydim2_advec_mom_kernel2_y = args[2].dat->size[1];
  int xdim3_advec_mom_kernel2_y = args[3].dat->size[0];
  int ydim3_advec_mom_kernel2_y = args[3].dat->size[1];

  //Halo Exchanges
  ops_H_D_exchanges_host(args, 4);
  ops_halo_exchanges(args,4,range);
  ops_H_D_exchanges_host(args, 4);

  if (OPS_diags > 1) {
    ops_timers_core(&c1,&t1);
    OPS_kernels[32].mpi_time += t1-t2;
  }

  #pragma omp parallel for collapse(2)
  for ( int n_z=start[2]; n_z<end[2]; n_z++ ){
    for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
      #ifdef intel
      #pragma omp simd
      #else
      #pragma simd
      #endif
      for ( int n_x=start[0]; n_x<end[0]; n_x++ ){
        

  vel1[OPS_ACC0(0,0,0)] = ( vel1[OPS_ACC0(0,0,0)] * node_mass_pre[OPS_ACC2(0,0,0)]  +
    mom_flux[OPS_ACC3(0,-1,0)] - mom_flux[OPS_ACC3(0,0,0)] ) / node_mass_post[OPS_ACC1(0,0,0)];

      }
    }
  }
  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[32].time += t2-t1;
  }
  ops_set_dirtybit_host(args, 4);
  ops_set_halo_dirtybit3(&args[0],range);

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c1,&t1);
    OPS_kernels[32].mpi_time += t1-t2;
    OPS_kernels[32].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[32].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[32].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_kernels[32].transfer += ops_compute_transfer(dim, start, end, &arg3);
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3


void ops_par_loop_advec_mom_kernel2_y(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->index = 32;
  #ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned) return;
  for ( int n=0; n<3; n++ ){
    desc->range[2*n] = sb->decomp_disp[n];desc->range[2*n+1] = sb->decomp_disp[n]+sb->decomp_size[n];
    if (desc->range[2*n] >= range[2*n]) {
      desc->range[2*n] = 0;
    }
    else {
      desc->range[2*n] = range[2*n] - desc->range[2*n];
    }
    if (sb->id_m[n]==MPI_PROC_NULL && range[2*n] < 0) desc->range[2*n] = range[2*n];
    if (desc->range[2*n+1] >= range[2*n+1]) {
      desc->range[2*n+1] = range[2*n+1] - sb->decomp_disp[n];
    }
    else {
      desc->range[2*n+1] = sb->decomp_size[n];
    }
    if (sb->id_p[n]==MPI_PROC_NULL && (range[2*n+1] > sb->decomp_disp[n]+sb->decomp_size[n]))
      desc->range[2*n+1] += (range[2*n+1]-sb->decomp_disp[n]-sb->decomp_size[n]);
  }
  #else //OPS_MPI
  for ( int i=0; i<6; i++ ){
    desc->range[i] = range[i];
  }
  #endif //OPS_MPI
  desc->nargs = 4;
  desc->args = (ops_arg*)malloc(4*sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->args[1] = arg1;
  desc->args[2] = arg2;
  desc->args[3] = arg3;
  desc->function = ops_par_loop_advec_mom_kernel2_y_execute;
  ops_enqueue_kernel(desc);
  }
