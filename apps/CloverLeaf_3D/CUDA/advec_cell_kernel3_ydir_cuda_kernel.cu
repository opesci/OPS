//
// auto-generated by ops.py on 2014-07-15 13:58
//

__constant__ int xdim0_advec_cell_kernel3_ydir;
__constant__ int ydim0_advec_cell_kernel3_ydir;
__constant__ int xdim1_advec_cell_kernel3_ydir;
__constant__ int ydim1_advec_cell_kernel3_ydir;
__constant__ int xdim2_advec_cell_kernel3_ydir;
__constant__ int ydim2_advec_cell_kernel3_ydir;
__constant__ int xdim3_advec_cell_kernel3_ydir;
__constant__ int ydim3_advec_cell_kernel3_ydir;
__constant__ int xdim4_advec_cell_kernel3_ydir;
__constant__ int ydim4_advec_cell_kernel3_ydir;
__constant__ int xdim5_advec_cell_kernel3_ydir;
__constant__ int ydim5_advec_cell_kernel3_ydir;
__constant__ int xdim6_advec_cell_kernel3_ydir;
__constant__ int ydim6_advec_cell_kernel3_ydir;
__constant__ int xdim7_advec_cell_kernel3_ydir;
__constant__ int ydim7_advec_cell_kernel3_ydir;

#define OPS_ACC0(x,y,z) (x+xdim0_advec_cell_kernel3_ydir*(y)+xdim0_advec_cell_kernel3_ydir*ydim0_advec_cell_kernel3_ydir*(z))
#define OPS_ACC1(x,y,z) (x+xdim1_advec_cell_kernel3_ydir*(y)+xdim1_advec_cell_kernel3_ydir*ydim1_advec_cell_kernel3_ydir*(z))
#define OPS_ACC2(x,y,z) (x+xdim2_advec_cell_kernel3_ydir*(y)+xdim2_advec_cell_kernel3_ydir*ydim2_advec_cell_kernel3_ydir*(z))
#define OPS_ACC3(x,y,z) (x+xdim3_advec_cell_kernel3_ydir*(y)+xdim3_advec_cell_kernel3_ydir*ydim3_advec_cell_kernel3_ydir*(z))
#define OPS_ACC4(x,y,z) (x+xdim4_advec_cell_kernel3_ydir*(y)+xdim4_advec_cell_kernel3_ydir*ydim4_advec_cell_kernel3_ydir*(z))
#define OPS_ACC5(x,y,z) (x+xdim5_advec_cell_kernel3_ydir*(y)+xdim5_advec_cell_kernel3_ydir*ydim5_advec_cell_kernel3_ydir*(z))
#define OPS_ACC6(x,y,z) (x+xdim6_advec_cell_kernel3_ydir*(y)+xdim6_advec_cell_kernel3_ydir*ydim6_advec_cell_kernel3_ydir*(z))
#define OPS_ACC7(x,y,z) (x+xdim7_advec_cell_kernel3_ydir*(y)+xdim7_advec_cell_kernel3_ydir*ydim7_advec_cell_kernel3_ydir*(z))

//user function
__device__

inline void advec_cell_kernel3_ydir( const double *vol_flux_y, const double *pre_vol, const int *yy,
                              const double *vertexdy,
                              const double *density1, const double *energy1 ,
                              double *mass_flux_y, double *ener_flux) {

  double sigma, sigmat, sigmav, sigmam, sigma3, sigma4;
  double diffuw, diffdw, limiter;
  double one_by_six = 1.0/6.0;

  int y_max=field.y_max;

  int upwind,donor,downwind,dif;





  if(vol_flux_y[OPS_ACC0(0,0,0)] > 0.0) {
    upwind   = -2;
    donor    = -1;
    downwind = 0;
    dif      = donor;
  }
  else if (yy[OPS_ACC2(0,1,0)] < y_max+2-2) {
    upwind   = 1;
    donor    = 0;
    downwind = -1;
    dif      = upwind;
  } else {
    upwind   = 0;
    donor    = 0;
    downwind = -1;
    dif      = upwind;
  }


  sigmat = fabs(vol_flux_y[OPS_ACC0(0,0,0)])/pre_vol[OPS_ACC1(0,donor,0)];
  sigma3 = (1.0 + sigmat)*(vertexdy[OPS_ACC3(0,0,0)]/vertexdy[OPS_ACC3(0,dif,0)]);
  sigma4 = 2.0 - sigmat;

  sigma = sigmat;
  sigmav = sigmat;

  diffuw = density1[OPS_ACC4(0,donor,0)] - density1[OPS_ACC4(0,upwind,0)];
  diffdw = density1[OPS_ACC4(0,downwind,0)] - density1[OPS_ACC4(0,donor,0)];

  if( (diffuw*diffdw) > 0.0)
    limiter=(1.0 - sigmav) * SIGN(1.0 , diffdw) *
    MIN( MIN(fabs(diffuw), fabs(diffdw)),
    one_by_six * (sigma3*fabs(diffuw) + sigma4 * fabs(diffdw)));
  else
    limiter=0.0;

  mass_flux_y[OPS_ACC6(0,0,0)] = (vol_flux_y[OPS_ACC0(0,0,0)]) * ( density1[OPS_ACC4(0,donor,0)] + limiter );

  sigmam = fabs(mass_flux_y[OPS_ACC6(0,0,0)])/( density1[OPS_ACC4(0,donor,0)] * pre_vol[OPS_ACC1(0,donor,0)]);
  diffuw = energy1[OPS_ACC5(0,donor,0)] - energy1[OPS_ACC5(0,upwind,0)];
  diffdw = energy1[OPS_ACC5(0,downwind,0)] - energy1[OPS_ACC5(0,donor,0)];

  if( (diffuw*diffdw) > 0.0)
    limiter = (1.0 - sigmam) * SIGN(1.0,diffdw) *
    MIN( MIN(fabs(diffuw), fabs(diffdw)),
    one_by_six * (sigma3 * fabs(diffuw) + sigma4 * fabs(diffdw)));
  else
    limiter=0.0;

  ener_flux[OPS_ACC7(0,0,0)] = mass_flux_y[OPS_ACC6(0,0,0)] * ( energy1[OPS_ACC5(0,donor,0)] + limiter );
}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3
#undef OPS_ACC4
#undef OPS_ACC5
#undef OPS_ACC6
#undef OPS_ACC7


__global__ void ops_advec_cell_kernel3_ydir(
const double* __restrict arg0,
const double* __restrict arg1,
const int* __restrict arg2,
const double* __restrict arg3,
const double* __restrict arg4,
const double* __restrict arg5,
double* __restrict arg6,
double* __restrict arg7,
int size0,
int size1,
int size2 ){


  int idx_z = blockDim.z * blockIdx.z + threadIdx.z;
  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 + idx_y * 1 * xdim0_advec_cell_kernel3_ydir + idx_z * 1 * xdim0_advec_cell_kernel3_ydir * ydim0_advec_cell_kernel3_ydir;
  arg1 += idx_x * 1 + idx_y * 1 * xdim1_advec_cell_kernel3_ydir + idx_z * 1 * xdim1_advec_cell_kernel3_ydir * ydim1_advec_cell_kernel3_ydir;
  arg2 += idx_x * 0 + idx_y * 1 * xdim2_advec_cell_kernel3_ydir + idx_z * 0 * xdim2_advec_cell_kernel3_ydir * ydim2_advec_cell_kernel3_ydir;
  arg3 += idx_x * 0 + idx_y * 1 * xdim3_advec_cell_kernel3_ydir + idx_z * 0 * xdim3_advec_cell_kernel3_ydir * ydim3_advec_cell_kernel3_ydir;
  arg4 += idx_x * 1 + idx_y * 1 * xdim4_advec_cell_kernel3_ydir + idx_z * 1 * xdim4_advec_cell_kernel3_ydir * ydim4_advec_cell_kernel3_ydir;
  arg5 += idx_x * 1 + idx_y * 1 * xdim5_advec_cell_kernel3_ydir + idx_z * 1 * xdim5_advec_cell_kernel3_ydir * ydim5_advec_cell_kernel3_ydir;
  arg6 += idx_x * 1 + idx_y * 1 * xdim6_advec_cell_kernel3_ydir + idx_z * 1 * xdim6_advec_cell_kernel3_ydir * ydim6_advec_cell_kernel3_ydir;
  arg7 += idx_x * 1 + idx_y * 1 * xdim7_advec_cell_kernel3_ydir + idx_z * 1 * xdim7_advec_cell_kernel3_ydir * ydim7_advec_cell_kernel3_ydir;

  if (idx_x < size0 && idx_y < size1 && idx_z < size2) {
    advec_cell_kernel3_ydir(arg0, arg1, arg2, arg3,
                   arg4, arg5, arg6, arg7);
  }

}

// host stub function
void ops_par_loop_advec_cell_kernel3_ydir(char const *name, ops_block Block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7) {

  ops_arg args[8] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7};

  sub_block_list sb = OPS_sub_block_list[Block->index];
  //compute localy allocated range for the sub-block
  int start_add[3];
  int end_add[3];
  for ( int n=0; n<3; n++ ){
    start_add[n] = sb->istart[n];end_add[n] = sb->iend[n]+1;
    if (start_add[n] >= range[2*n]) {
      start_add[n] = 0;
    }
    else {
      start_add[n] = range[2*n] - start_add[n];
    }
    if (end_add[n] >= range[2*n+1]) {
      end_add[n] = range[2*n+1] - sb->istart[n];
    }
    else {
      end_add[n] = sb->sizes[n];
    }
  }


  int x_size = MAX(0,end_add[0]-start_add[0]);
  int y_size = MAX(0,end_add[1]-start_add[1]);
  int z_size = MAX(0,end_add[2]-start_add[2]);

  int xdim0 = args[0].dat->block_size[0]*args[0].dat->dim;
  int ydim0 = args[0].dat->block_size[1];
  int xdim1 = args[1].dat->block_size[0]*args[1].dat->dim;
  int ydim1 = args[1].dat->block_size[1];
  int xdim2 = args[2].dat->block_size[0]*args[2].dat->dim;
  int ydim2 = args[2].dat->block_size[1];
  int xdim3 = args[3].dat->block_size[0]*args[3].dat->dim;
  int ydim3 = args[3].dat->block_size[1];
  int xdim4 = args[4].dat->block_size[0]*args[4].dat->dim;
  int ydim4 = args[4].dat->block_size[1];
  int xdim5 = args[5].dat->block_size[0]*args[5].dat->dim;
  int ydim5 = args[5].dat->block_size[1];
  int xdim6 = args[6].dat->block_size[0]*args[6].dat->dim;
  int ydim6 = args[6].dat->block_size[1];
  int xdim7 = args[7].dat->block_size[0]*args[7].dat->dim;
  int ydim7 = args[7].dat->block_size[1];


  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(13,"advec_cell_kernel3_ydir");
  ops_timers_core(&c2,&t2);

  if (OPS_kernels[13].count == 0) {
    cudaMemcpyToSymbol( xdim0_advec_cell_kernel3_ydir, &xdim0, sizeof(int) );
    cudaMemcpyToSymbol( ydim0_advec_cell_kernel3_ydir, &ydim0, sizeof(int) );
    cudaMemcpyToSymbol( xdim1_advec_cell_kernel3_ydir, &xdim1, sizeof(int) );
    cudaMemcpyToSymbol( ydim1_advec_cell_kernel3_ydir, &ydim1, sizeof(int) );
    cudaMemcpyToSymbol( xdim2_advec_cell_kernel3_ydir, &xdim2, sizeof(int) );
    cudaMemcpyToSymbol( ydim2_advec_cell_kernel3_ydir, &ydim2, sizeof(int) );
    cudaMemcpyToSymbol( xdim3_advec_cell_kernel3_ydir, &xdim3, sizeof(int) );
    cudaMemcpyToSymbol( ydim3_advec_cell_kernel3_ydir, &ydim3, sizeof(int) );
    cudaMemcpyToSymbol( xdim4_advec_cell_kernel3_ydir, &xdim4, sizeof(int) );
    cudaMemcpyToSymbol( ydim4_advec_cell_kernel3_ydir, &ydim4, sizeof(int) );
    cudaMemcpyToSymbol( xdim5_advec_cell_kernel3_ydir, &xdim5, sizeof(int) );
    cudaMemcpyToSymbol( ydim5_advec_cell_kernel3_ydir, &ydim5, sizeof(int) );
    cudaMemcpyToSymbol( xdim6_advec_cell_kernel3_ydir, &xdim6, sizeof(int) );
    cudaMemcpyToSymbol( ydim6_advec_cell_kernel3_ydir, &ydim6, sizeof(int) );
    cudaMemcpyToSymbol( xdim7_advec_cell_kernel3_ydir, &xdim7, sizeof(int) );
    cudaMemcpyToSymbol( ydim7_advec_cell_kernel3_ydir, &ydim7, sizeof(int) );
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, z_size);
  dim3 block(OPS_block_size_x,OPS_block_size_y,1);



  int dat0 = args[0].dat->size;
  int dat1 = args[1].dat->size;
  int dat2 = args[2].dat->size;
  int dat3 = args[3].dat->size;
  int dat4 = args[4].dat->size;
  int dat5 = args[5].dat->size;
  int dat6 = args[6].dat->size;
  int dat7 = args[7].dat->size;

  char *p_a[8];

  //set up initial pointers
  int base0 = dat0 * 1 * 
  (start_add[0] * args[0].stencil->stride[0] - args[0].dat->offset[0]);
  base0 = base0+ dat0 *
    args[0].dat->block_size[0] *
    (start_add[1] * args[0].stencil->stride[1] - args[0].dat->offset[1]);
  base0 = base0+ dat0 *
    args[0].dat->block_size[0] *
    args[0].dat->block_size[1] *
    (start_add[2] * args[0].stencil->stride[2] - args[0].dat->offset[2]);
  p_a[0] = (char *)args[0].data_d + base0;

  int base1 = dat1 * 1 * 
  (start_add[0] * args[1].stencil->stride[0] - args[1].dat->offset[0]);
  base1 = base1+ dat1 *
    args[1].dat->block_size[0] *
    (start_add[1] * args[1].stencil->stride[1] - args[1].dat->offset[1]);
  base1 = base1+ dat1 *
    args[1].dat->block_size[0] *
    args[1].dat->block_size[1] *
    (start_add[2] * args[1].stencil->stride[2] - args[1].dat->offset[2]);
  p_a[1] = (char *)args[1].data_d + base1;

  int base2 = dat2 * 1 * 
  (start_add[0] * args[2].stencil->stride[0] - args[2].dat->offset[0]);
  base2 = base2+ dat2 *
    args[2].dat->block_size[0] *
    (start_add[1] * args[2].stencil->stride[1] - args[2].dat->offset[1]);
  base2 = base2+ dat2 *
    args[2].dat->block_size[0] *
    args[2].dat->block_size[1] *
    (start_add[2] * args[2].stencil->stride[2] - args[2].dat->offset[2]);
  p_a[2] = (char *)args[2].data_d + base2;

  int base3 = dat3 * 1 * 
  (start_add[0] * args[3].stencil->stride[0] - args[3].dat->offset[0]);
  base3 = base3+ dat3 *
    args[3].dat->block_size[0] *
    (start_add[1] * args[3].stencil->stride[1] - args[3].dat->offset[1]);
  base3 = base3+ dat3 *
    args[3].dat->block_size[0] *
    args[3].dat->block_size[1] *
    (start_add[2] * args[3].stencil->stride[2] - args[3].dat->offset[2]);
  p_a[3] = (char *)args[3].data_d + base3;

  int base4 = dat4 * 1 * 
  (start_add[0] * args[4].stencil->stride[0] - args[4].dat->offset[0]);
  base4 = base4+ dat4 *
    args[4].dat->block_size[0] *
    (start_add[1] * args[4].stencil->stride[1] - args[4].dat->offset[1]);
  base4 = base4+ dat4 *
    args[4].dat->block_size[0] *
    args[4].dat->block_size[1] *
    (start_add[2] * args[4].stencil->stride[2] - args[4].dat->offset[2]);
  p_a[4] = (char *)args[4].data_d + base4;

  int base5 = dat5 * 1 * 
  (start_add[0] * args[5].stencil->stride[0] - args[5].dat->offset[0]);
  base5 = base5+ dat5 *
    args[5].dat->block_size[0] *
    (start_add[1] * args[5].stencil->stride[1] - args[5].dat->offset[1]);
  base5 = base5+ dat5 *
    args[5].dat->block_size[0] *
    args[5].dat->block_size[1] *
    (start_add[2] * args[5].stencil->stride[2] - args[5].dat->offset[2]);
  p_a[5] = (char *)args[5].data_d + base5;

  int base6 = dat6 * 1 * 
  (start_add[0] * args[6].stencil->stride[0] - args[6].dat->offset[0]);
  base6 = base6+ dat6 *
    args[6].dat->block_size[0] *
    (start_add[1] * args[6].stencil->stride[1] - args[6].dat->offset[1]);
  base6 = base6+ dat6 *
    args[6].dat->block_size[0] *
    args[6].dat->block_size[1] *
    (start_add[2] * args[6].stencil->stride[2] - args[6].dat->offset[2]);
  p_a[6] = (char *)args[6].data_d + base6;

  int base7 = dat7 * 1 * 
  (start_add[0] * args[7].stencil->stride[0] - args[7].dat->offset[0]);
  base7 = base7+ dat7 *
    args[7].dat->block_size[0] *
    (start_add[1] * args[7].stencil->stride[1] - args[7].dat->offset[1]);
  base7 = base7+ dat7 *
    args[7].dat->block_size[0] *
    args[7].dat->block_size[1] *
    (start_add[2] * args[7].stencil->stride[2] - args[7].dat->offset[2]);
  p_a[7] = (char *)args[7].data_d + base7;


  ops_H_D_exchanges_cuda(args, 8);
  ops_halo_exchanges(args,8,range);

  ops_timers_core(&c1,&t1);
  OPS_kernels[13].mpi_time += t1-t2;


  //call kernel wrapper function, passing in pointers to data
  ops_advec_cell_kernel3_ydir<<<grid, block >>> (  (double *)p_a[0], (double *)p_a[1],
           (int *)p_a[2], (double *)p_a[3],
           (double *)p_a[4], (double *)p_a[5],
           (double *)p_a[6], (double *)p_a[7],x_size, y_size, z_size);

  if (OPS_diags>1) {
    cutilSafeCall(cudaDeviceSynchronize());
  }
  ops_timers_core(&c2,&t2);
  OPS_kernels[13].time += t2-t1;
  ops_set_dirtybit_cuda(args, 8);
  ops_set_halo_dirtybit3(&args[6],range);
  ops_set_halo_dirtybit3(&args[7],range);

  //Update kernel record
  OPS_kernels[13].count++;
  OPS_kernels[13].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[13].transfer += ops_compute_transfer(dim, range, &arg1);
  OPS_kernels[13].transfer += ops_compute_transfer(dim, range, &arg2);
  OPS_kernels[13].transfer += ops_compute_transfer(dim, range, &arg3);
  OPS_kernels[13].transfer += ops_compute_transfer(dim, range, &arg4);
  OPS_kernels[13].transfer += ops_compute_transfer(dim, range, &arg5);
  OPS_kernels[13].transfer += ops_compute_transfer(dim, range, &arg6);
  OPS_kernels[13].transfer += ops_compute_transfer(dim, range, &arg7);
}
