//
// auto-generated by ops.py
//

//user function

// host stub function
#ifndef OPS_LAZY
void ops_par_loop_update_halo_kernel1_b1(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7) {
#else
void ops_par_loop_update_halo_kernel1_b1_execute(ops_kernel_descriptor *desc) {
  ops_block block = desc->block;
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
  #endif

  //Timing
  double __t1,__t2,__c1,__c2;

  ops_arg args[8] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7};



  #if defined(CHECKPOINTING) && !defined(OPS_LAZY)
  if (!ops_checkpointing_before(args,8,range,12)) return;
  #endif

  if (OPS_diags > 1) {
    ops_timing_realloc(12,"update_halo_kernel1_b1");
    OPS_kernels[12].count++;
    ops_timers_core(&__c2,&__t2);
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "update_halo_kernel1_b1");
  #endif


  //compute locally allocated range for the sub-block
  int start[3];
  int end[3];
  #ifdef OPS_MPI
  int arg_idx[3];
  #endif
  #if defined(OPS_LAZY) || !defined(OPS_MPI)
  for ( int n=0; n<3; n++ ){
    start[n] = range[2*n];end[n] = range[2*n+1];
  }
  #else
  if (compute_ranges(args, 8,block, range, start, end, arg_idx) < 0) return;
  #endif


  //initialize global variable with the dimension of dats
  int xdim0_update_halo_kernel1_b1 = args[0].dat->size[0];
  int ydim0_update_halo_kernel1_b1 = args[0].dat->size[1];
  int xdim1_update_halo_kernel1_b1 = args[1].dat->size[0];
  int ydim1_update_halo_kernel1_b1 = args[1].dat->size[1];
  int xdim2_update_halo_kernel1_b1 = args[2].dat->size[0];
  int ydim2_update_halo_kernel1_b1 = args[2].dat->size[1];
  int xdim3_update_halo_kernel1_b1 = args[3].dat->size[0];
  int ydim3_update_halo_kernel1_b1 = args[3].dat->size[1];
  int xdim4_update_halo_kernel1_b1 = args[4].dat->size[0];
  int ydim4_update_halo_kernel1_b1 = args[4].dat->size[1];
  int xdim5_update_halo_kernel1_b1 = args[5].dat->size[0];
  int ydim5_update_halo_kernel1_b1 = args[5].dat->size[1];
  int xdim6_update_halo_kernel1_b1 = args[6].dat->size[0];
  int ydim6_update_halo_kernel1_b1 = args[6].dat->size[1];

  //set up initial pointers and exchange halos if necessary
  int base0 = args[0].dat->base_offset;
  double *__restrict__ density0_p = (double *)(args[0].data + base0);

  int base1 = args[1].dat->base_offset;
  double *__restrict__ density1_p = (double *)(args[1].data + base1);

  int base2 = args[2].dat->base_offset;
  double *__restrict__ energy0_p = (double *)(args[2].data + base2);

  int base3 = args[3].dat->base_offset;
  double *__restrict__ energy1_p = (double *)(args[3].data + base3);

  int base4 = args[4].dat->base_offset;
  double *__restrict__ pressure_p = (double *)(args[4].data + base4);

  int base5 = args[5].dat->base_offset;
  double *__restrict__ viscosity_p = (double *)(args[5].data + base5);

  int base6 = args[6].dat->base_offset;
  double *__restrict__ soundspeed_p = (double *)(args[6].data + base6);

  int *__restrict__ fields = (int *)args[7].data;

  #ifndef OPS_LAZY
  //Halo Exchanges
  ops_H_D_exchanges_host(args, 8);
  ops_halo_exchanges(args,8,range);
  ops_H_D_exchanges_host(args, 8);
  #endif

  if (OPS_diags > 1) {
    ops_timers_core(&__c1,&__t1);
    OPS_kernels[12].mpi_time += __t1-__t2;
  }

  #pragma omp parallel for collapse(2)
  for ( int n_z=start[2]; n_z<end[2]; n_z++ ){
    for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
      #ifdef __INTEL_COMPILER
      #pragma loop_count(10000)
#pragma omp simd
#elif defined(__clang__)
#pragma clang loop vectorize(assume_safety)
#elif defined(__GNUC__)
#pragma simd
#pragma GCC ivdep
#else
#pragma simd
#endif
      for ( int n_x=start[0]; n_x<end[0]; n_x++ ){
        ACC<double> density0(
            xdim0_update_halo_kernel1_b1, ydim0_update_halo_kernel1_b1,
            density0_p + n_x * 1 + n_y * xdim0_update_halo_kernel1_b1 * 1 +
                n_z * xdim0_update_halo_kernel1_b1 *
                    ydim0_update_halo_kernel1_b1 * 1);
        ACC<double> density1(
            xdim1_update_halo_kernel1_b1, ydim1_update_halo_kernel1_b1,
            density1_p + n_x * 1 + n_y * xdim1_update_halo_kernel1_b1 * 1 +
                n_z * xdim1_update_halo_kernel1_b1 *
                    ydim1_update_halo_kernel1_b1 * 1);
        ACC<double> energy0(
            xdim2_update_halo_kernel1_b1, ydim2_update_halo_kernel1_b1,
            energy0_p + n_x * 1 + n_y * xdim2_update_halo_kernel1_b1 * 1 +
                n_z * xdim2_update_halo_kernel1_b1 *
                    ydim2_update_halo_kernel1_b1 * 1);
        ACC<double> energy1(
            xdim3_update_halo_kernel1_b1, ydim3_update_halo_kernel1_b1,
            energy1_p + n_x * 1 + n_y * xdim3_update_halo_kernel1_b1 * 1 +
                n_z * xdim3_update_halo_kernel1_b1 *
                    ydim3_update_halo_kernel1_b1 * 1);
        ACC<double> pressure(
            xdim4_update_halo_kernel1_b1, ydim4_update_halo_kernel1_b1,
            pressure_p + n_x * 1 + n_y * xdim4_update_halo_kernel1_b1 * 1 +
                n_z * xdim4_update_halo_kernel1_b1 *
                    ydim4_update_halo_kernel1_b1 * 1);
        ACC<double> viscosity(
            xdim5_update_halo_kernel1_b1, ydim5_update_halo_kernel1_b1,
            viscosity_p + n_x * 1 + n_y * xdim5_update_halo_kernel1_b1 * 1 +
                n_z * xdim5_update_halo_kernel1_b1 *
                    ydim5_update_halo_kernel1_b1 * 1);
        ACC<double> soundspeed(
            xdim6_update_halo_kernel1_b1, ydim6_update_halo_kernel1_b1,
            soundspeed_p + n_x * 1 + n_y * xdim6_update_halo_kernel1_b1 * 1 +
                n_z * xdim6_update_halo_kernel1_b1 *
                    ydim6_update_halo_kernel1_b1 * 1);

        if (fields[FIELD_DENSITY0] == 1)
          density0(0, 0, 0) = density0(0, 1, 0);
        if (fields[FIELD_DENSITY1] == 1)
          density1(0, 0, 0) = density1(0, 1, 0);
        if (fields[FIELD_ENERGY0] == 1)
          energy0(0, 0, 0) = energy0(0, 1, 0);
        if (fields[FIELD_ENERGY1] == 1)
          energy1(0, 0, 0) = energy1(0, 1, 0);
        if (fields[FIELD_PRESSURE] == 1)
          pressure(0, 0, 0) = pressure(0, 1, 0);
        if (fields[FIELD_VISCOSITY] == 1)
          viscosity(0, 0, 0) = viscosity(0, 1, 0);
        if (fields[FIELD_SOUNDSPEED] == 1)
          soundspeed(0, 0, 0) = soundspeed(0, 1, 0);
      }
    }
  }
  if (OPS_diags > 1) {
    ops_timers_core(&__c2,&__t2);
    OPS_kernels[12].time += __t2-__t1;
  }
  #ifndef OPS_LAZY
  ops_set_dirtybit_host(args, 8);
  ops_set_halo_dirtybit3(&args[0],range);
  ops_set_halo_dirtybit3(&args[1],range);
  ops_set_halo_dirtybit3(&args[2],range);
  ops_set_halo_dirtybit3(&args[3],range);
  ops_set_halo_dirtybit3(&args[4],range);
  ops_set_halo_dirtybit3(&args[5],range);
  ops_set_halo_dirtybit3(&args[6],range);
  #endif

  if (OPS_diags > 1) {
    //Update kernel record
    ops_timers_core(&__c1,&__t1);
    OPS_kernels[12].mpi_time += __t1-__t2;
    OPS_kernels[12].transfer += ops_compute_transfer(dim, start, end, &arg0);
    OPS_kernels[12].transfer += ops_compute_transfer(dim, start, end, &arg1);
    OPS_kernels[12].transfer += ops_compute_transfer(dim, start, end, &arg2);
    OPS_kernels[12].transfer += ops_compute_transfer(dim, start, end, &arg3);
    OPS_kernels[12].transfer += ops_compute_transfer(dim, start, end, &arg4);
    OPS_kernels[12].transfer += ops_compute_transfer(dim, start, end, &arg5);
    OPS_kernels[12].transfer += ops_compute_transfer(dim, start, end, &arg6);
  }
}


#ifdef OPS_LAZY
void ops_par_loop_update_halo_kernel1_b1(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7) {
  ops_kernel_descriptor *desc = (ops_kernel_descriptor *)malloc(sizeof(ops_kernel_descriptor));
  desc->name = name;
  desc->block = block;
  desc->dim = dim;
  desc->device = 1;
  desc->index = 12;
  desc->hash = 5381;
  desc->hash = ((desc->hash << 5) + desc->hash) + 12;
  for ( int i=0; i<6; i++ ){
    desc->range[i] = range[i];
    desc->orig_range[i] = range[i];
    desc->hash = ((desc->hash << 5) + desc->hash) + range[i];
  }
  desc->nargs = 8;
  desc->args = (ops_arg*)malloc(8*sizeof(ops_arg));
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
  char *tmp = (char*)malloc(NUM_FIELDS*sizeof(int));
  memcpy(tmp, arg7.data,NUM_FIELDS*sizeof(int));
  desc->args[7].data = tmp;
  desc->function = ops_par_loop_update_halo_kernel1_b1_execute;
  if (OPS_diags > 1) {
    ops_timing_realloc(12,"update_halo_kernel1_b1");
  }
  ops_enqueue_kernel(desc);
}
#endif