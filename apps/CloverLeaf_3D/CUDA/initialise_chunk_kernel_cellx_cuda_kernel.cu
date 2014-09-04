//
// auto-generated by ops.py
//
__constant__ int xdim0_initialise_chunk_kernel_cellx;
__constant__ int ydim0_initialise_chunk_kernel_cellx;
__constant__ int xdim1_initialise_chunk_kernel_cellx;
__constant__ int ydim1_initialise_chunk_kernel_cellx;
__constant__ int xdim2_initialise_chunk_kernel_cellx;
__constant__ int ydim2_initialise_chunk_kernel_cellx;

#define OPS_ACC0(x,y,z) (x+xdim0_initialise_chunk_kernel_cellx*(y)+xdim0_initialise_chunk_kernel_cellx*ydim0_initialise_chunk_kernel_cellx*(z))
#define OPS_ACC1(x,y,z) (x+xdim1_initialise_chunk_kernel_cellx*(y)+xdim1_initialise_chunk_kernel_cellx*ydim1_initialise_chunk_kernel_cellx*(z))
#define OPS_ACC2(x,y,z) (x+xdim2_initialise_chunk_kernel_cellx*(y)+xdim2_initialise_chunk_kernel_cellx*ydim2_initialise_chunk_kernel_cellx*(z))

//user function
__device__

void initialise_chunk_kernel_cellx(const double *vertexx, double* cellx, double *celldx) {
  double d_x = (grid.xmax - grid.xmin)/(double)grid.x_cells;
  cellx[OPS_ACC1(0,0,0)]  = 0.5*( vertexx[OPS_ACC0(0,0,0)] + vertexx[OPS_ACC0(1,0,0)] );
  celldx[OPS_ACC2(0,0,0)]  = d_x;




}



#undef OPS_ACC0
#undef OPS_ACC1
#undef OPS_ACC2


__global__ void ops_initialise_chunk_kernel_cellx(
const double* __restrict arg0,
double* __restrict arg1,
double* __restrict arg2,
int size0,
int size1,
int size2 ){


  int idx_z = blockDim.z * blockIdx.z + threadIdx.z;
  int idx_y = blockDim.y * blockIdx.y + threadIdx.y;
  int idx_x = blockDim.x * blockIdx.x + threadIdx.x;

  arg0 += idx_x * 1 + idx_y * 0 * xdim0_initialise_chunk_kernel_cellx + idx_z * 0 * xdim0_initialise_chunk_kernel_cellx * ydim0_initialise_chunk_kernel_cellx;
  arg1 += idx_x * 1 + idx_y * 0 * xdim1_initialise_chunk_kernel_cellx + idx_z * 0 * xdim1_initialise_chunk_kernel_cellx * ydim1_initialise_chunk_kernel_cellx;
  arg2 += idx_x * 1 + idx_y * 0 * xdim2_initialise_chunk_kernel_cellx + idx_z * 0 * xdim2_initialise_chunk_kernel_cellx * ydim2_initialise_chunk_kernel_cellx;

  if (idx_x < size0 && idx_y < size1 && idx_z < size2) {
    initialise_chunk_kernel_cellx(arg0, arg1, arg2);
  }

}

// host stub function
void ops_par_loop_initialise_chunk_kernel_cellx(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2) {

  ops_arg args[3] = { arg0, arg1, arg2};


  ops_timing_realloc(136,"initialise_chunk_kernel_cellx");
  OPS_kernels[136].count++;

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

  int x_size = MAX(0,end[0]-start[0]);
  int y_size = MAX(0,end[1]-start[1]);
  int z_size = MAX(0,end[2]-start[2]);

  int xdim0 = args[0].dat->size[0]*args[0].dat->dim;
  int ydim0 = args[0].dat->size[1];
  int xdim1 = args[1].dat->size[0]*args[1].dat->dim;
  int ydim1 = args[1].dat->size[1];
  int xdim2 = args[2].dat->size[0]*args[2].dat->dim;
  int ydim2 = args[2].dat->size[1];


  //Timing
  double t1,t2,c1,c2;
  ops_timers_core(&c2,&t2);

  if (OPS_kernels[136].count == 1) {
    cudaMemcpyToSymbol( xdim0_initialise_chunk_kernel_cellx, &xdim0, sizeof(int) );
    cudaMemcpyToSymbol( ydim0_initialise_chunk_kernel_cellx, &ydim0, sizeof(int) );
    cudaMemcpyToSymbol( xdim1_initialise_chunk_kernel_cellx, &xdim1, sizeof(int) );
    cudaMemcpyToSymbol( ydim1_initialise_chunk_kernel_cellx, &ydim1, sizeof(int) );
    cudaMemcpyToSymbol( xdim2_initialise_chunk_kernel_cellx, &xdim2, sizeof(int) );
    cudaMemcpyToSymbol( ydim2_initialise_chunk_kernel_cellx, &ydim2, sizeof(int) );
  }



  dim3 grid( (x_size-1)/OPS_block_size_x+ 1, (y_size-1)/OPS_block_size_y + 1, z_size);
  dim3 tblock(OPS_block_size_x,OPS_block_size_y,1);



  int dat0 = args[0].dat->elem_size;
  int dat1 = args[1].dat->elem_size;
  int dat2 = args[2].dat->elem_size;

  char *p_a[3];

  //set up initial pointers
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
  base0 = base0+ dat0 *
    args[0].dat->size[0] *
    args[0].dat->size[1] *
    (start[2] * args[0].stencil->stride[2] - args[0].dat->base[2] - d_m[2]);
  p_a[0] = (char *)args[0].data_d + base0;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[1].dat->d_m[d] + OPS_sub_dat_list[args[1].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[1].dat->d_m[d];
  #endif //OPS_MPI
  int base1 = dat1 * 1 * 
  (start[0] * args[1].stencil->stride[0] - args[1].dat->base[0] - d_m[0]);
  base1 = base1+ dat1 *
    args[1].dat->size[0] *
    (start[1] * args[1].stencil->stride[1] - args[1].dat->base[1] - d_m[1]);
  base1 = base1+ dat1 *
    args[1].dat->size[0] *
    args[1].dat->size[1] *
    (start[2] * args[1].stencil->stride[2] - args[1].dat->base[2] - d_m[2]);
  p_a[1] = (char *)args[1].data_d + base1;

  #ifdef OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[2].dat->d_m[d] + OPS_sub_dat_list[args[2].dat->index]->d_im[d];
  #else //OPS_MPI
  for (int d = 0; d < dim; d++) d_m[d] = args[2].dat->d_m[d];
  #endif //OPS_MPI
  int base2 = dat2 * 1 * 
  (start[0] * args[2].stencil->stride[0] - args[2].dat->base[0] - d_m[0]);
  base2 = base2+ dat2 *
    args[2].dat->size[0] *
    (start[1] * args[2].stencil->stride[1] - args[2].dat->base[1] - d_m[1]);
  base2 = base2+ dat2 *
    args[2].dat->size[0] *
    args[2].dat->size[1] *
    (start[2] * args[2].stencil->stride[2] - args[2].dat->base[2] - d_m[2]);
  p_a[2] = (char *)args[2].data_d + base2;


  ops_H_D_exchanges_device(args, 3);
  ops_halo_exchanges(args,3,range);

  ops_timers_core(&c1,&t1);
  OPS_kernels[136].mpi_time += t1-t2;


  //call kernel wrapper function, passing in pointers to data
  ops_initialise_chunk_kernel_cellx<<<grid, tblock >>> (  (double *)p_a[0], (double *)p_a[1],
           (double *)p_a[2],x_size, y_size, z_size);

  if (OPS_diags>1) {
    cutilSafeCall(cudaDeviceSynchronize());
  }
  ops_timers_core(&c2,&t2);
  OPS_kernels[136].time += t2-t1;
  ops_set_dirtybit_device(args, 3);
  ops_set_halo_dirtybit3(&args[1],range);
  ops_set_halo_dirtybit3(&args[2],range);

  //Update kernel record
  OPS_kernels[136].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[136].transfer += ops_compute_transfer(dim, range, &arg1);
  OPS_kernels[136].transfer += ops_compute_transfer(dim, range, &arg2);
}
