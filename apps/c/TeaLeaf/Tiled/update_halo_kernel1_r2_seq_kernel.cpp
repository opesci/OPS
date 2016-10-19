//
// auto-generated by ops.py
//
#define OPS_ACC0(x,y) (n_x*1+n_y*xdim0_update_halo_kernel1_r2*1+x+xdim0_update_halo_kernel1_r2*(y))
#define OPS_ACC1(x,y) (n_x*1+n_y*xdim1_update_halo_kernel1_r2*1+x+xdim1_update_halo_kernel1_r2*(y))
#define OPS_ACC2(x,y) (n_x*1+n_y*xdim2_update_halo_kernel1_r2*1+x+xdim2_update_halo_kernel1_r2*(y))
#define OPS_ACC3(x,y) (n_x*1+n_y*xdim3_update_halo_kernel1_r2*1+x+xdim3_update_halo_kernel1_r2*(y))
#define OPS_ACC4(x,y) (n_x*1+n_y*xdim4_update_halo_kernel1_r2*1+x+xdim4_update_halo_kernel1_r2*(y))
#define OPS_ACC5(x,y) (n_x*1+n_y*xdim5_update_halo_kernel1_r2*1+x+xdim5_update_halo_kernel1_r2*(y))


//user function

// host stub function
void ops_par_loop_update_halo_kernel1_r2_execute(ops_kernel_descriptor *desc) {
  int dim = desc->dim;
  int *range = desc->range;
  ops_arg arg0 = desc->args[0];
  ops_arg arg1 = desc->args[1];
  ops_arg arg2 = desc->args[2];
  ops_arg arg3 = desc->args[3];
  ops_arg arg4 = desc->args[4];
  ops_arg arg5 = desc->args[5];
  ops_arg arg6 = desc->args[6];

  //Timing
  double t1,t2,c1,c2;

  ops_arg args[7] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6};



  #ifdef CHECKPOINTING
  if (!ops_checkpointing_before(args,7,range,55)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(55,"update_halo_kernel1_r2");
    OPS_kernels[55].count++;
    ops_timers_core(&c2,&t2);
  }

  //compute locally allocated range for the sub-block
  int start[2];
  int end[2];

  for ( int n=0; n<2; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "update_halo_kernel1_r2");
  #endif



  //set up initial pointers and exchange halos if necessary
  int base0 = args[0].dat->base_offset;
  double * __restrict__ density0 = (double *)(args[0].data + base0);

  int base1 = args[1].dat->base_offset;
  double * __restrict__ energy0 = (double *)(args[1].data + base1);

  int base2 = args[2].dat->base_offset;
  double * __restrict__ energy1 = (double *)(args[2].data + base2);

  int base3 = args[3].dat->base_offset;
  double * __restrict__ u = (double *)(args[3].data + base3);

  int base4 = args[4].dat->base_offset;
  double * __restrict__ p = (double *)(args[4].data + base4);

  int base5 = args[5].dat->base_offset;
  double * __restrict__ sd = (double *)(args[5].data + base5);

  const int * __restrict__ fields = (int *)args[6].data;



  //initialize global variable with the dimension of dats
  int xdim0_update_halo_kernel1_r2 = args[0].dat->size[0];
  int xdim1_update_halo_kernel1_r2 = args[1].dat->size[0];
  int xdim2_update_halo_kernel1_r2 = args[2].dat->size[0];
  int xdim3_update_halo_kernel1_r2 = args[3].dat->size[0];
  int xdim4_update_halo_kernel1_r2 = args[4].dat->size[0];
  int xdim5_update_halo_kernel1_r2 = args[5].dat->size[0];

  //Halo Exchanges
  ops_H_D_exchanges_host(args, 7);
  ops_halo_exchanges(args,7,range);
  ops_H_D_exchanges_host(args, 7);

  if (OPS_diags > 1) {
    ops_timers_core(&c1,&t1);
    OPS_kernels[55].mpi_time += t1-t2;
  }

  #pragma omp parallel for
  for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
#ifdef intel
#pragma omp simd
#else
#pragma simd
#endif
    for ( int n_x=start[0]; n_x<end[0]; n_x++ ){
      
  if(fields[FIELD_DENSITY] == 1) density0[OPS_ACC0(0,0)] = density0[OPS_ACC0(-3,0)];
  if(fields[FIELD_ENERGY0] == 1) energy0[OPS_ACC1(0,0)] = energy0[OPS_ACC1(-3,0)];
  if(fields[FIELD_ENERGY1] == 1) energy1[OPS_ACC2(0,0)] = energy1[OPS_ACC2(-3,0)];
  if(fields[FIELD_U] == 1) u[OPS_ACC3(0,0)] = u[OPS_ACC3(-3,0)];
  if(fields[FIELD_P] == 1) p[OPS_ACC4(0,0)] = p[OPS_ACC4(-3,0)];
  if(fields[FIELD_SD] == 1) sd[OPS_ACC5(0,0)] = sd[OPS_ACC5(-3,0)];


    }
  }
  if (OPS_diags > 1) {
    ops_timers_core(&c2,&t2);
    OPS_kernels[55].time += t2-t1;
  }
  ops_set_dirtybit_host(args, 7);
  ops_set_halo_dirtybit3(&args[0],range);
  ops_set_halo_dirtybit3(&args[1],range);
  ops_set_halo_dirtybit3(&args[2],range);
  ops_set_halo_dirtybit3(&args[3],range);
  ops_set_halo_dirtybit3(&args[4],range);
  ops_set_halo_dirtybit3(&args[5],range);

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&c1,&t1);
    OPS_kernels[55].mpi_time += t1-t2;
    OPS_kernels[55].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[55].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[55].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_kernels[55].transfer += ops_compute_transfer(dim, start, end, &arg3);
    OPS_kernels[55].transfer += ops_compute_transfer(dim, start, end, &arg4);
    OPS_kernels[55].transfer += ops_compute_transfer(dim, start, end, &arg5);
  }
}
#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5


void ops_par_loop_update_halo_kernel1_r2(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->index = 55;
  #ifdef OPS_MPI
  sub_block_list sb = OPS_sub_block_list[block->index];
  if (!sb->owned) return;
  for ( int n=0; n<2; n++ ){
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
  for ( int i=0; i<4; i++ ){
    desc->range[i] = range[i];
  }
  #endif //OPS_MPI
  desc->nargs = 7;
  desc->args = (ops_arg*)malloc(7*sizeof(ops_arg));
  desc->args[0] = arg0;
  desc->args[1] = arg1;
  desc->args[2] = arg2;
  desc->args[3] = arg3;
  desc->args[4] = arg4;
  desc->args[5] = arg5;
  desc->args[6] = arg6;
  char *tmp = (char*)malloc(NUM_FIELDS*sizeof(int));
  memcpy(tmp, arg6.data,NUM_FIELDS*sizeof(int));
  desc->args[6].data = tmp;
  desc->function = ops_par_loop_update_halo_kernel1_r2_execute;
  ops_enqueue_kernel(desc);
  }
