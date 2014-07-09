//
// auto-generated by ops.py on 2014-07-09 10:24
//

#ifdef _OPENMP
#include <omp.h>
#endif

//user function
inline 
void initialise_chunk_kernel_cellx(const double *vertexx, double* cellx, double *celldx) {

  int x_min=field.x_min-2;
  int x_max=field.x_max-2;
  int y_min=field.y_min-2;
  int y_max=field.y_max-2;

  double min_x, min_y, d_x, d_y;

  d_x = (grid.xmax - grid.xmin)/(double)grid.x_cells;
  d_y = (grid.ymax - grid.ymin)/(double)grid.y_cells;

  min_x=grid.xmin+d_x;
  min_y=grid.ymin+d_y;

  cellx[OPS_ACC1(0,0)]  = 0.5*( vertexx[OPS_ACC0(0,0)] + vertexx[OPS_ACC0(1,0)] );
  celldx[OPS_ACC2(0,0)]  = d_x;

}



// host stub function
void ops_par_loop_initialise_chunk_kernel_cellx(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2) {

  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(77,"initialise_chunk_kernel_cellx");
  ops_timers_core(&c1,&t1);


  int  offs[3][2];
  ops_arg args[3] = { arg0, arg1, arg2};


  sub_block_list sb = OPS_sub_block_list[block->index];
  //compute localy allocated range for the sub-block

  int start[2];
  int end[2];

  for ( int n=0; n<2; n++ ){
    start[n] = sb->istart[n];end[n] = sb->iend[n]+1;
    if (start[n] >= range[2*n]) {
      start[n] = 0;
    }
    else {
      start[n] = range[2*n] - start[n];
    }
    if (end[n] >= range[2*n+1]) {
      end[n] = range[2*n+1] - sb->istart[n];
    }
    else {
      end[n] = sb->sizes[n];
    }
  }

  #ifdef OPS_DEBUG
  ops_register_args(args, "initialise_chunk_kernel_cellx");
  #endif

  offs[0][0] = args[0].stencil->stride[0]*1;  //unit step in x dimension
  offs[0][1] = off2D(1, &start[0],
      &end[0],args[0].dat->block_size, args[0].stencil->stride) - offs[0][0];

  offs[1][0] = args[1].stencil->stride[0]*1;  //unit step in x dimension
  offs[1][1] = off2D(1, &start[0],
      &end[0],args[1].dat->block_size, args[1].stencil->stride) - offs[1][0];

  offs[2][0] = args[2].stencil->stride[0]*1;  //unit step in x dimension
  offs[2][1] = off2D(1, &start[0],
      &end[0],args[2].dat->block_size, args[2].stencil->stride) - offs[2][0];



  int off0_0 = offs[0][0];
  int off0_1 = offs[0][1];
  int dat0 = args[0].dat->size;
  int off1_0 = offs[1][0];
  int off1_1 = offs[1][1];
  int dat1 = args[1].dat->size;
  int off2_0 = offs[2][0];
  int off2_1 = offs[2][1];
  int dat2 = args[2].dat->size;


  #ifdef _OPENMP
  int nthreads = omp_get_max_threads( );
  #else
  int nthreads = 1;
  #endif
  xdim0 = args[0].dat->block_size[0]*args[0].dat->dim;
  xdim1 = args[1].dat->block_size[0]*args[1].dat->dim;
  xdim2 = args[2].dat->block_size[0]*args[2].dat->dim;

  //Halo Exchanges
  ops_halo_exchanges(args,3,range);

  ops_H_D_exchanges(args, 3);


  ops_timers_core(&c2,&t2);
  OPS_kernels[77].mpi_time += t2-t1;


  #pragma omp parallel for
  for ( int thr=0; thr<nthreads; thr++ ){

    int y_size = end[1]-start[1];
    char *p_a[3];

    int start_i = start[1] + ((y_size-1)/nthreads+1)*thr;
    int finish_i = start[1] + MIN(((y_size-1)/nthreads+1)*(thr+1),y_size);

    //get address per thread
    int start0 = start[0];
    int start1 = start_i;

    //set up initial pointers 
    int base0 = dat0 * 1 * 
    (start0 * args[0].stencil->stride[0] - args[0].dat->offset[0]);
    base0 = base0+ dat0 *
      args[0].dat->block_size[0] *
      (start1 * args[0].stencil->stride[1] - args[0].dat->offset[1]);
    p_a[0] = (char *)args[0].data + base0;

    int base1 = dat1 * 1 * 
    (start0 * args[1].stencil->stride[0] - args[1].dat->offset[0]);
    base1 = base1+ dat1 *
      args[1].dat->block_size[0] *
      (start1 * args[1].stencil->stride[1] - args[1].dat->offset[1]);
    p_a[1] = (char *)args[1].data + base1;

    int base2 = dat2 * 1 * 
    (start0 * args[2].stencil->stride[0] - args[2].dat->offset[0]);
    base2 = base2+ dat2 *
      args[2].dat->block_size[0] *
      (start1 * args[2].stencil->stride[1] - args[2].dat->offset[1]);
    p_a[2] = (char *)args[2].data + base2;


    for ( int n_y=start_i; n_y<finish_i; n_y++ ){
      for ( int n_x=start[0]; n_x<start[0]+(end[0]-start[0])/SIMD_VEC; n_x++ ){
        //call kernel function, passing in pointers to data -vectorised
        #pragma simd
        for ( int i=0; i<SIMD_VEC; i++ ){
          initialise_chunk_kernel_cellx(  (const double * restrict)p_a[0]+ i*1, (double * restrict)p_a[1]+ i*1, (double * restrict)p_a[2]+ i*1 );

        }

        //shift pointers to data x direction
        p_a[0]= p_a[0] + (dat0 * off0_0)*SIMD_VEC;
        p_a[1]= p_a[1] + (dat1 * off1_0)*SIMD_VEC;
        p_a[2]= p_a[2] + (dat2 * off2_0)*SIMD_VEC;
      }

      for ( int n_x=start[0]+((end[0]-start[0])/SIMD_VEC)*SIMD_VEC; n_x<end[0]; n_x++ ){
        //call kernel function, passing in pointers to data - remainder
        initialise_chunk_kernel_cellx(  (const double * restrict)p_a[0], (double * restrict)p_a[1], (double * restrict)p_a[2] );


        //shift pointers to data x direction
        p_a[0]= p_a[0] + (dat0 * off0_0);
        p_a[1]= p_a[1] + (dat1 * off1_0);
        p_a[2]= p_a[2] + (dat2 * off2_0);
      }

      //shift pointers to data y direction
      p_a[0]= p_a[0] + (dat0 * off0_1);
      p_a[1]= p_a[1] + (dat1 * off1_1);
      p_a[2]= p_a[2] + (dat2 * off2_1);
    }
  }

  ops_timers_core(&c1,&t1);
  OPS_kernels[77].time += t1-t2;

  ops_set_dirtybit_host(args, 3);

  ops_set_halo_dirtybit3(&args[1],range);
  ops_set_halo_dirtybit3(&args[2],range);

  #ifdef OPS_DEBUG
  ops_dump3(arg1.dat,"initialise_chunk_kernel_cellx");
  ops_dump3(arg2.dat,"initialise_chunk_kernel_cellx");
  #endif

  //Update kernel record
  ops_timers_core(&c2,&t2);
  OPS_kernels[77].count++;
  OPS_kernels[77].mpi_time += t2-t1;
  OPS_kernels[77].transfer += ops_compute_transfer(dim, range, &arg0);
  OPS_kernels[77].transfer += ops_compute_transfer(dim, range, &arg1);
  OPS_kernels[77].transfer += ops_compute_transfer(dim, range, &arg2);
}
