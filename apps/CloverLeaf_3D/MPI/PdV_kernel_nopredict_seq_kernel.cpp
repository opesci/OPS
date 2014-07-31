//
<<<<<<< HEAD
// auto-generated by ops.py on 2014-07-16 16:41
=======
// auto-generated by ops.py on 2014-07-15 13:58
>>>>>>> cdd149f... fixes brought over from Wayne's 3D version, CPU versions tested
//

//user function
#include "PdV_kernel.h"

// host stub function
void ops_par_loop_PdV_kernel_nopredict(char const *name, ops_block block, int dim, int* range,
 ops_arg arg0, ops_arg arg1, ops_arg arg2, ops_arg arg3,
 ops_arg arg4, ops_arg arg5, ops_arg arg6, ops_arg arg7,
 ops_arg arg8, ops_arg arg9, ops_arg arg10, ops_arg arg11,
 ops_arg arg12, ops_arg arg13, ops_arg arg14, ops_arg arg15,
 ops_arg arg16) {

  char *p_a[17];
  int  offs[17][3];
  ops_arg args[17] = { arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13, arg14, arg15, arg16};


  sub_block_list sb = OPS_sub_block_list[block->index];
  //compute localy allocated range for the sub-block
  int start[3];
  int end[3];

  for ( int n=0; n<3; n++ ){
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
  ops_register_args(args, "PdV_kernel_nopredict");
  #endif

  offs[0][0] = args[0].stencil->stride[0]*1;  //unit step in x dimension
  offs[0][1] = off3D(1, &start[0],
      &end[0],args[0].dat->block_size, args[0].stencil->stride) - offs[0][0];
  offs[0][2] = off3D(2, &start[0],
      &end[0],args[0].dat->block_size, args[0].stencil->stride) - offs[0][1] - offs[0][0];

  offs[1][0] = args[1].stencil->stride[0]*1;  //unit step in x dimension
  offs[1][1] = off3D(1, &start[0],
      &end[0],args[1].dat->block_size, args[1].stencil->stride) - offs[1][0];
  offs[1][2] = off3D(2, &start[0],
      &end[0],args[1].dat->block_size, args[1].stencil->stride) - offs[1][1] - offs[1][0];

  offs[2][0] = args[2].stencil->stride[0]*1;  //unit step in x dimension
  offs[2][1] = off3D(1, &start[0],
      &end[0],args[2].dat->block_size, args[2].stencil->stride) - offs[2][0];
  offs[2][2] = off3D(2, &start[0],
      &end[0],args[2].dat->block_size, args[2].stencil->stride) - offs[2][1] - offs[2][0];

  offs[3][0] = args[3].stencil->stride[0]*1;  //unit step in x dimension
  offs[3][1] = off3D(1, &start[0],
      &end[0],args[3].dat->block_size, args[3].stencil->stride) - offs[3][0];
  offs[3][2] = off3D(2, &start[0],
      &end[0],args[3].dat->block_size, args[3].stencil->stride) - offs[3][1] - offs[3][0];

  offs[4][0] = args[4].stencil->stride[0]*1;  //unit step in x dimension
  offs[4][1] = off3D(1, &start[0],
      &end[0],args[4].dat->block_size, args[4].stencil->stride) - offs[4][0];
  offs[4][2] = off3D(2, &start[0],
      &end[0],args[4].dat->block_size, args[4].stencil->stride) - offs[4][1] - offs[4][0];

  offs[5][0] = args[5].stencil->stride[0]*1;  //unit step in x dimension
  offs[5][1] = off3D(1, &start[0],
      &end[0],args[5].dat->block_size, args[5].stencil->stride) - offs[5][0];
  offs[5][2] = off3D(2, &start[0],
      &end[0],args[5].dat->block_size, args[5].stencil->stride) - offs[5][1] - offs[5][0];

  offs[6][0] = args[6].stencil->stride[0]*1;  //unit step in x dimension
  offs[6][1] = off3D(1, &start[0],
      &end[0],args[6].dat->block_size, args[6].stencil->stride) - offs[6][0];
  offs[6][2] = off3D(2, &start[0],
      &end[0],args[6].dat->block_size, args[6].stencil->stride) - offs[6][1] - offs[6][0];

  offs[7][0] = args[7].stencil->stride[0]*1;  //unit step in x dimension
  offs[7][1] = off3D(1, &start[0],
      &end[0],args[7].dat->block_size, args[7].stencil->stride) - offs[7][0];
  offs[7][2] = off3D(2, &start[0],
      &end[0],args[7].dat->block_size, args[7].stencil->stride) - offs[7][1] - offs[7][0];

  offs[8][0] = args[8].stencil->stride[0]*1;  //unit step in x dimension
  offs[8][1] = off3D(1, &start[0],
      &end[0],args[8].dat->block_size, args[8].stencil->stride) - offs[8][0];
  offs[8][2] = off3D(2, &start[0],
      &end[0],args[8].dat->block_size, args[8].stencil->stride) - offs[8][1] - offs[8][0];

  offs[9][0] = args[9].stencil->stride[0]*1;  //unit step in x dimension
  offs[9][1] = off3D(1, &start[0],
      &end[0],args[9].dat->block_size, args[9].stencil->stride) - offs[9][0];
  offs[9][2] = off3D(2, &start[0],
      &end[0],args[9].dat->block_size, args[9].stencil->stride) - offs[9][1] - offs[9][0];

  offs[10][0] = args[10].stencil->stride[0]*1;  //unit step in x dimension
  offs[10][1] = off3D(1, &start[0],
      &end[0],args[10].dat->block_size, args[10].stencil->stride) - offs[10][0];
  offs[10][2] = off3D(2, &start[0],
      &end[0],args[10].dat->block_size, args[10].stencil->stride) - offs[10][1] - offs[10][0];

  offs[11][0] = args[11].stencil->stride[0]*1;  //unit step in x dimension
  offs[11][1] = off3D(1, &start[0],
      &end[0],args[11].dat->block_size, args[11].stencil->stride) - offs[11][0];
  offs[11][2] = off3D(2, &start[0],
      &end[0],args[11].dat->block_size, args[11].stencil->stride) - offs[11][1] - offs[11][0];

  offs[12][0] = args[12].stencil->stride[0]*1;  //unit step in x dimension
  offs[12][1] = off3D(1, &start[0],
      &end[0],args[12].dat->block_size, args[12].stencil->stride) - offs[12][0];
  offs[12][2] = off3D(2, &start[0],
      &end[0],args[12].dat->block_size, args[12].stencil->stride) - offs[12][1] - offs[12][0];

  offs[13][0] = args[13].stencil->stride[0]*1;  //unit step in x dimension
  offs[13][1] = off3D(1, &start[0],
      &end[0],args[13].dat->block_size, args[13].stencil->stride) - offs[13][0];
  offs[13][2] = off3D(2, &start[0],
      &end[0],args[13].dat->block_size, args[13].stencil->stride) - offs[13][1] - offs[13][0];

  offs[14][0] = args[14].stencil->stride[0]*1;  //unit step in x dimension
  offs[14][1] = off3D(1, &start[0],
      &end[0],args[14].dat->block_size, args[14].stencil->stride) - offs[14][0];
  offs[14][2] = off3D(2, &start[0],
      &end[0],args[14].dat->block_size, args[14].stencil->stride) - offs[14][1] - offs[14][0];

  offs[15][0] = args[15].stencil->stride[0]*1;  //unit step in x dimension
  offs[15][1] = off3D(1, &start[0],
      &end[0],args[15].dat->block_size, args[15].stencil->stride) - offs[15][0];
  offs[15][2] = off3D(2, &start[0],
      &end[0],args[15].dat->block_size, args[15].stencil->stride) - offs[15][1] - offs[15][0];

  offs[16][0] = args[16].stencil->stride[0]*1;  //unit step in x dimension
  offs[16][1] = off3D(1, &start[0],
      &end[0],args[16].dat->block_size, args[16].stencil->stride) - offs[16][0];
  offs[16][2] = off3D(2, &start[0],
      &end[0],args[16].dat->block_size, args[16].stencil->stride) - offs[16][1] - offs[16][0];



  //Timing
  double t1,t2,c1,c2;
  ops_timing_realloc(5,"PdV_kernel_nopredict");
  ops_timers_core(&c2,&t2);

  int off0_0 = offs[0][0];
  int off0_1 = offs[0][1];
  int off0_2 = offs[0][2];
  int dat0 = args[0].dat->size;
  int off1_0 = offs[1][0];
  int off1_1 = offs[1][1];
  int off1_2 = offs[1][2];
  int dat1 = args[1].dat->size;
  int off2_0 = offs[2][0];
  int off2_1 = offs[2][1];
  int off2_2 = offs[2][2];
  int dat2 = args[2].dat->size;
  int off3_0 = offs[3][0];
  int off3_1 = offs[3][1];
  int off3_2 = offs[3][2];
  int dat3 = args[3].dat->size;
  int off4_0 = offs[4][0];
  int off4_1 = offs[4][1];
  int off4_2 = offs[4][2];
  int dat4 = args[4].dat->size;
  int off5_0 = offs[5][0];
  int off5_1 = offs[5][1];
  int off5_2 = offs[5][2];
  int dat5 = args[5].dat->size;
  int off6_0 = offs[6][0];
  int off6_1 = offs[6][1];
  int off6_2 = offs[6][2];
  int dat6 = args[6].dat->size;
  int off7_0 = offs[7][0];
  int off7_1 = offs[7][1];
  int off7_2 = offs[7][2];
  int dat7 = args[7].dat->size;
  int off8_0 = offs[8][0];
  int off8_1 = offs[8][1];
  int off8_2 = offs[8][2];
  int dat8 = args[8].dat->size;
  int off9_0 = offs[9][0];
  int off9_1 = offs[9][1];
  int off9_2 = offs[9][2];
  int dat9 = args[9].dat->size;
  int off10_0 = offs[10][0];
  int off10_1 = offs[10][1];
  int off10_2 = offs[10][2];
  int dat10 = args[10].dat->size;
  int off11_0 = offs[11][0];
  int off11_1 = offs[11][1];
  int off11_2 = offs[11][2];
  int dat11 = args[11].dat->size;
  int off12_0 = offs[12][0];
  int off12_1 = offs[12][1];
  int off12_2 = offs[12][2];
  int dat12 = args[12].dat->size;
  int off13_0 = offs[13][0];
  int off13_1 = offs[13][1];
  int off13_2 = offs[13][2];
  int dat13 = args[13].dat->size;
  int off14_0 = offs[14][0];
  int off14_1 = offs[14][1];
  int off14_2 = offs[14][2];
  int dat14 = args[14].dat->size;
  int off15_0 = offs[15][0];
  int off15_1 = offs[15][1];
  int off15_2 = offs[15][2];
  int dat15 = args[15].dat->size;
  int off16_0 = offs[16][0];
  int off16_1 = offs[16][1];
  int off16_2 = offs[16][2];
  int dat16 = args[16].dat->size;

  //set up initial pointers and exchange halos if nessasary
  int base0 = dat0 * 1 * 
  (start[0] * args[0].stencil->stride[0] - args[0].dat->offset[0]);
  base0 = base0+ dat0 *
    args[0].dat->block_size[0] *
    (start[1] * args[0].stencil->stride[1] - args[0].dat->offset[1]);
  base0 = base0+ dat0 *
    args[0].dat->block_size[0] *
    args[0].dat->block_size[1] *
    (start[2] * args[0].stencil->stride[2] - args[0].dat->offset[2]);
  p_a[0] = (char *)args[0].data + base0;

  int base1 = dat1 * 1 * 
  (start[0] * args[1].stencil->stride[0] - args[1].dat->offset[0]);
  base1 = base1+ dat1 *
    args[1].dat->block_size[0] *
    (start[1] * args[1].stencil->stride[1] - args[1].dat->offset[1]);
  base1 = base1+ dat1 *
    args[1].dat->block_size[0] *
    args[1].dat->block_size[1] *
    (start[2] * args[1].stencil->stride[2] - args[1].dat->offset[2]);
  p_a[1] = (char *)args[1].data + base1;

  int base2 = dat2 * 1 * 
  (start[0] * args[2].stencil->stride[0] - args[2].dat->offset[0]);
  base2 = base2+ dat2 *
    args[2].dat->block_size[0] *
    (start[1] * args[2].stencil->stride[1] - args[2].dat->offset[1]);
  base2 = base2+ dat2 *
    args[2].dat->block_size[0] *
    args[2].dat->block_size[1] *
    (start[2] * args[2].stencil->stride[2] - args[2].dat->offset[2]);
  p_a[2] = (char *)args[2].data + base2;

  int base3 = dat3 * 1 * 
  (start[0] * args[3].stencil->stride[0] - args[3].dat->offset[0]);
  base3 = base3+ dat3 *
    args[3].dat->block_size[0] *
    (start[1] * args[3].stencil->stride[1] - args[3].dat->offset[1]);
  base3 = base3+ dat3 *
    args[3].dat->block_size[0] *
    args[3].dat->block_size[1] *
    (start[2] * args[3].stencil->stride[2] - args[3].dat->offset[2]);
  p_a[3] = (char *)args[3].data + base3;

  int base4 = dat4 * 1 * 
  (start[0] * args[4].stencil->stride[0] - args[4].dat->offset[0]);
  base4 = base4+ dat4 *
    args[4].dat->block_size[0] *
    (start[1] * args[4].stencil->stride[1] - args[4].dat->offset[1]);
  base4 = base4+ dat4 *
    args[4].dat->block_size[0] *
    args[4].dat->block_size[1] *
    (start[2] * args[4].stencil->stride[2] - args[4].dat->offset[2]);
  p_a[4] = (char *)args[4].data + base4;

  int base5 = dat5 * 1 * 
  (start[0] * args[5].stencil->stride[0] - args[5].dat->offset[0]);
  base5 = base5+ dat5 *
    args[5].dat->block_size[0] *
    (start[1] * args[5].stencil->stride[1] - args[5].dat->offset[1]);
  base5 = base5+ dat5 *
    args[5].dat->block_size[0] *
    args[5].dat->block_size[1] *
    (start[2] * args[5].stencil->stride[2] - args[5].dat->offset[2]);
  p_a[5] = (char *)args[5].data + base5;

  int base6 = dat6 * 1 * 
  (start[0] * args[6].stencil->stride[0] - args[6].dat->offset[0]);
  base6 = base6+ dat6 *
    args[6].dat->block_size[0] *
    (start[1] * args[6].stencil->stride[1] - args[6].dat->offset[1]);
  base6 = base6+ dat6 *
    args[6].dat->block_size[0] *
    args[6].dat->block_size[1] *
    (start[2] * args[6].stencil->stride[2] - args[6].dat->offset[2]);
  p_a[6] = (char *)args[6].data + base6;

  int base7 = dat7 * 1 * 
  (start[0] * args[7].stencil->stride[0] - args[7].dat->offset[0]);
  base7 = base7+ dat7 *
    args[7].dat->block_size[0] *
    (start[1] * args[7].stencil->stride[1] - args[7].dat->offset[1]);
  base7 = base7+ dat7 *
    args[7].dat->block_size[0] *
    args[7].dat->block_size[1] *
    (start[2] * args[7].stencil->stride[2] - args[7].dat->offset[2]);
  p_a[7] = (char *)args[7].data + base7;

  int base8 = dat8 * 1 * 
  (start[0] * args[8].stencil->stride[0] - args[8].dat->offset[0]);
  base8 = base8+ dat8 *
    args[8].dat->block_size[0] *
    (start[1] * args[8].stencil->stride[1] - args[8].dat->offset[1]);
  base8 = base8+ dat8 *
    args[8].dat->block_size[0] *
    args[8].dat->block_size[1] *
    (start[2] * args[8].stencil->stride[2] - args[8].dat->offset[2]);
  p_a[8] = (char *)args[8].data + base8;

  int base9 = dat9 * 1 * 
  (start[0] * args[9].stencil->stride[0] - args[9].dat->offset[0]);
  base9 = base9+ dat9 *
    args[9].dat->block_size[0] *
    (start[1] * args[9].stencil->stride[1] - args[9].dat->offset[1]);
  base9 = base9+ dat9 *
    args[9].dat->block_size[0] *
    args[9].dat->block_size[1] *
    (start[2] * args[9].stencil->stride[2] - args[9].dat->offset[2]);
  p_a[9] = (char *)args[9].data + base9;

  int base10 = dat10 * 1 * 
  (start[0] * args[10].stencil->stride[0] - args[10].dat->offset[0]);
  base10 = base10+ dat10 *
    args[10].dat->block_size[0] *
    (start[1] * args[10].stencil->stride[1] - args[10].dat->offset[1]);
  base10 = base10+ dat10 *
    args[10].dat->block_size[0] *
    args[10].dat->block_size[1] *
    (start[2] * args[10].stencil->stride[2] - args[10].dat->offset[2]);
  p_a[10] = (char *)args[10].data + base10;

  int base11 = dat11 * 1 * 
  (start[0] * args[11].stencil->stride[0] - args[11].dat->offset[0]);
  base11 = base11+ dat11 *
    args[11].dat->block_size[0] *
    (start[1] * args[11].stencil->stride[1] - args[11].dat->offset[1]);
  base11 = base11+ dat11 *
    args[11].dat->block_size[0] *
    args[11].dat->block_size[1] *
    (start[2] * args[11].stencil->stride[2] - args[11].dat->offset[2]);
  p_a[11] = (char *)args[11].data + base11;

  int base12 = dat12 * 1 * 
  (start[0] * args[12].stencil->stride[0] - args[12].dat->offset[0]);
  base12 = base12+ dat12 *
    args[12].dat->block_size[0] *
    (start[1] * args[12].stencil->stride[1] - args[12].dat->offset[1]);
  base12 = base12+ dat12 *
    args[12].dat->block_size[0] *
    args[12].dat->block_size[1] *
    (start[2] * args[12].stencil->stride[2] - args[12].dat->offset[2]);
  p_a[12] = (char *)args[12].data + base12;

  int base13 = dat13 * 1 * 
  (start[0] * args[13].stencil->stride[0] - args[13].dat->offset[0]);
  base13 = base13+ dat13 *
    args[13].dat->block_size[0] *
    (start[1] * args[13].stencil->stride[1] - args[13].dat->offset[1]);
  base13 = base13+ dat13 *
    args[13].dat->block_size[0] *
    args[13].dat->block_size[1] *
    (start[2] * args[13].stencil->stride[2] - args[13].dat->offset[2]);
  p_a[13] = (char *)args[13].data + base13;

  int base14 = dat14 * 1 * 
  (start[0] * args[14].stencil->stride[0] - args[14].dat->offset[0]);
  base14 = base14+ dat14 *
    args[14].dat->block_size[0] *
    (start[1] * args[14].stencil->stride[1] - args[14].dat->offset[1]);
  base14 = base14+ dat14 *
    args[14].dat->block_size[0] *
    args[14].dat->block_size[1] *
    (start[2] * args[14].stencil->stride[2] - args[14].dat->offset[2]);
  p_a[14] = (char *)args[14].data + base14;

  int base15 = dat15 * 1 * 
  (start[0] * args[15].stencil->stride[0] - args[15].dat->offset[0]);
  base15 = base15+ dat15 *
    args[15].dat->block_size[0] *
    (start[1] * args[15].stencil->stride[1] - args[15].dat->offset[1]);
  base15 = base15+ dat15 *
    args[15].dat->block_size[0] *
    args[15].dat->block_size[1] *
    (start[2] * args[15].stencil->stride[2] - args[15].dat->offset[2]);
  p_a[15] = (char *)args[15].data + base15;

  int base16 = dat16 * 1 * 
  (start[0] * args[16].stencil->stride[0] - args[16].dat->offset[0]);
  base16 = base16+ dat16 *
    args[16].dat->block_size[0] *
    (start[1] * args[16].stencil->stride[1] - args[16].dat->offset[1]);
  base16 = base16+ dat16 *
    args[16].dat->block_size[0] *
    args[16].dat->block_size[1] *
    (start[2] * args[16].stencil->stride[2] - args[16].dat->offset[2]);
  p_a[16] = (char *)args[16].data + base16;


  ops_H_D_exchanges(args,17);
  ops_halo_exchanges(args,17,range);

  ops_timers_core(&c1,&t1);
  OPS_kernels[5].mpi_time += t1-t2;

  xdim0 = args[0].dat->block_size[0]*args[0].dat->dim;
  ydim0 = args[0].dat->block_size[1];
  xdim1 = args[1].dat->block_size[0]*args[1].dat->dim;
  ydim1 = args[1].dat->block_size[1];
  xdim2 = args[2].dat->block_size[0]*args[2].dat->dim;
  ydim2 = args[2].dat->block_size[1];
  xdim3 = args[3].dat->block_size[0]*args[3].dat->dim;
  ydim3 = args[3].dat->block_size[1];
  xdim4 = args[4].dat->block_size[0]*args[4].dat->dim;
  ydim4 = args[4].dat->block_size[1];
  xdim5 = args[5].dat->block_size[0]*args[5].dat->dim;
  ydim5 = args[5].dat->block_size[1];
  xdim6 = args[6].dat->block_size[0]*args[6].dat->dim;
  ydim6 = args[6].dat->block_size[1];
  xdim7 = args[7].dat->block_size[0]*args[7].dat->dim;
  ydim7 = args[7].dat->block_size[1];
  xdim8 = args[8].dat->block_size[0]*args[8].dat->dim;
  ydim8 = args[8].dat->block_size[1];
  xdim9 = args[9].dat->block_size[0]*args[9].dat->dim;
  ydim9 = args[9].dat->block_size[1];
  xdim10 = args[10].dat->block_size[0]*args[10].dat->dim;
  ydim10 = args[10].dat->block_size[1];
  xdim11 = args[11].dat->block_size[0]*args[11].dat->dim;
  ydim11 = args[11].dat->block_size[1];
  xdim12 = args[12].dat->block_size[0]*args[12].dat->dim;
  ydim12 = args[12].dat->block_size[1];
  xdim13 = args[13].dat->block_size[0]*args[13].dat->dim;
  ydim13 = args[13].dat->block_size[1];
  xdim14 = args[14].dat->block_size[0]*args[14].dat->dim;
  ydim14 = args[14].dat->block_size[1];
  xdim15 = args[15].dat->block_size[0]*args[15].dat->dim;
  ydim15 = args[15].dat->block_size[1];
  xdim16 = args[16].dat->block_size[0]*args[16].dat->dim;
  ydim16 = args[16].dat->block_size[1];

  int n_x;
  for ( int n_z=start[2]; n_z<end[2]; n_z++ ){
    for ( int n_y=start[1]; n_y<end[1]; n_y++ ){
      #pragma novector
      for( n_x=start[0]; n_x<start[0]+((end[0]-start[0])/SIMD_VEC)*SIMD_VEC; n_x+=SIMD_VEC ) {
        //call kernel function, passing in pointers to data -vectorised
        #pragma simd
        for ( int i=0; i<SIMD_VEC; i++ ){
          PdV_kernel_nopredict(  (double *)p_a[0]+ i*1, (double *)p_a[1]+ i*1, (double *)p_a[2]+ i*1,
           (double *)p_a[3]+ i*1, (double *)p_a[4]+ i*1, (double *)p_a[5]+ i*1, (double *)p_a[6]+ i*1,
           (double *)p_a[7]+ i*1, (double *)p_a[8]+ i*1, (double *)p_a[9]+ i*1, (double *)p_a[10]+ i*1,
           (double *)p_a[11]+ i*1, (double *)p_a[12]+ i*1, (double *)p_a[13]+ i*1, (double *)p_a[14]+ i*1,
           (double *)p_a[15]+ i*1, (double *)p_a[16]+ i*1 );

        }

        //shift pointers to data x direction
        p_a[0]= p_a[0] + (dat0 * off0_0)*SIMD_VEC;
        p_a[1]= p_a[1] + (dat1 * off1_0)*SIMD_VEC;
        p_a[2]= p_a[2] + (dat2 * off2_0)*SIMD_VEC;
        p_a[3]= p_a[3] + (dat3 * off3_0)*SIMD_VEC;
        p_a[4]= p_a[4] + (dat4 * off4_0)*SIMD_VEC;
        p_a[5]= p_a[5] + (dat5 * off5_0)*SIMD_VEC;
        p_a[6]= p_a[6] + (dat6 * off6_0)*SIMD_VEC;
        p_a[7]= p_a[7] + (dat7 * off7_0)*SIMD_VEC;
        p_a[8]= p_a[8] + (dat8 * off8_0)*SIMD_VEC;
        p_a[9]= p_a[9] + (dat9 * off9_0)*SIMD_VEC;
        p_a[10]= p_a[10] + (dat10 * off10_0)*SIMD_VEC;
        p_a[11]= p_a[11] + (dat11 * off11_0)*SIMD_VEC;
        p_a[12]= p_a[12] + (dat12 * off12_0)*SIMD_VEC;
        p_a[13]= p_a[13] + (dat13 * off13_0)*SIMD_VEC;
        p_a[14]= p_a[14] + (dat14 * off14_0)*SIMD_VEC;
        p_a[15]= p_a[15] + (dat15 * off15_0)*SIMD_VEC;
        p_a[16]= p_a[16] + (dat16 * off16_0)*SIMD_VEC;
      }

      for ( int n_x=start[0]+((end[0]-start[0])/SIMD_VEC)*SIMD_VEC; n_x<end[0]; n_x++ ){
          //call kernel function, passing in pointers to data - remainder
          PdV_kernel_nopredict(  (double *)p_a[0], (double *)p_a[1], (double *)p_a[2],
           (double *)p_a[3], (double *)p_a[4], (double *)p_a[5], (double *)p_a[6],
           (double *)p_a[7], (double *)p_a[8], (double *)p_a[9], (double *)p_a[10],
           (double *)p_a[11], (double *)p_a[12], (double *)p_a[13], (double *)p_a[14],
           (double *)p_a[15], (double *)p_a[16] );


          //shift pointers to data x direction
          p_a[0]= p_a[0] + (dat0 * off0_0);
          p_a[1]= p_a[1] + (dat1 * off1_0);
          p_a[2]= p_a[2] + (dat2 * off2_0);
          p_a[3]= p_a[3] + (dat3 * off3_0);
          p_a[4]= p_a[4] + (dat4 * off4_0);
          p_a[5]= p_a[5] + (dat5 * off5_0);
          p_a[6]= p_a[6] + (dat6 * off6_0);
          p_a[7]= p_a[7] + (dat7 * off7_0);
          p_a[8]= p_a[8] + (dat8 * off8_0);
          p_a[9]= p_a[9] + (dat9 * off9_0);
          p_a[10]= p_a[10] + (dat10 * off10_0);
          p_a[11]= p_a[11] + (dat11 * off11_0);
          p_a[12]= p_a[12] + (dat12 * off12_0);
          p_a[13]= p_a[13] + (dat13 * off13_0);
          p_a[14]= p_a[14] + (dat14 * off14_0);
          p_a[15]= p_a[15] + (dat15 * off15_0);
          p_a[16]= p_a[16] + (dat16 * off16_0);
        }

        //shift pointers to data y direction
        p_a[0]= p_a[0] + (dat0 * off0_1);
        p_a[1]= p_a[1] + (dat1 * off1_1);
        p_a[2]= p_a[2] + (dat2 * off2_1);
        p_a[3]= p_a[3] + (dat3 * off3_1);
        p_a[4]= p_a[4] + (dat4 * off4_1);
        p_a[5]= p_a[5] + (dat5 * off5_1);
        p_a[6]= p_a[6] + (dat6 * off6_1);
        p_a[7]= p_a[7] + (dat7 * off7_1);
        p_a[8]= p_a[8] + (dat8 * off8_1);
        p_a[9]= p_a[9] + (dat9 * off9_1);
        p_a[10]= p_a[10] + (dat10 * off10_1);
        p_a[11]= p_a[11] + (dat11 * off11_1);
        p_a[12]= p_a[12] + (dat12 * off12_1);
        p_a[13]= p_a[13] + (dat13 * off13_1);
        p_a[14]= p_a[14] + (dat14 * off14_1);
        p_a[15]= p_a[15] + (dat15 * off15_1);
        p_a[16]= p_a[16] + (dat16 * off16_1);
      }
      //shift pointers to data z direction
      p_a[0]= p_a[0] + (dat0 * off0_2);
      p_a[1]= p_a[1] + (dat1 * off1_2);
      p_a[2]= p_a[2] + (dat2 * off2_2);
      p_a[3]= p_a[3] + (dat3 * off3_2);
      p_a[4]= p_a[4] + (dat4 * off4_2);
      p_a[5]= p_a[5] + (dat5 * off5_2);
      p_a[6]= p_a[6] + (dat6 * off6_2);
      p_a[7]= p_a[7] + (dat7 * off7_2);
      p_a[8]= p_a[8] + (dat8 * off8_2);
      p_a[9]= p_a[9] + (dat9 * off9_2);
      p_a[10]= p_a[10] + (dat10 * off10_2);
      p_a[11]= p_a[11] + (dat11 * off11_2);
      p_a[12]= p_a[12] + (dat12 * off12_2);
      p_a[13]= p_a[13] + (dat13 * off13_2);
      p_a[14]= p_a[14] + (dat14 * off14_2);
      p_a[15]= p_a[15] + (dat15 * off15_2);
      p_a[16]= p_a[16] + (dat16 * off16_2);
    }
    ops_timers_core(&c2,&t2);
<<<<<<< HEAD
    OPS_kernels[6].time += t2-t1;
    ops_set_dirtybit_host(args, 17);
=======
    OPS_kernels[5].time += t2-t1;
>>>>>>> cdd149f... fixes brought over from Wayne's 3D version, CPU versions tested
    ops_set_halo_dirtybit3(&args[6],range);
    ops_set_halo_dirtybit3(&args[10],range);
    ops_set_halo_dirtybit3(&args[13],range);

    #ifdef OPS_DEBUG
    ops_dump3(arg6.dat,"PdV_kernel_nopredict");
    ops_dump3(arg10.dat,"PdV_kernel_nopredict");
    ops_dump3(arg13.dat,"PdV_kernel_nopredict");
    #endif

    //Update kernel record
    OPS_kernels[5].count++;
    OPS_kernels[5].transfer += ops_compute_transfer(dim, range, &arg0);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, range, &arg1);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, range, &arg2);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, range, &arg3);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, range, &arg4);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, range, &arg5);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, range, &arg6);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, range, &arg7);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, range, &arg8);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, range, &arg9);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, range, &arg10);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, range, &arg11);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, range, &arg12);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, range, &arg13);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, range, &arg14);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, range, &arg15);
    OPS_kernels[5].transfer += ops_compute_transfer(dim, range, &arg16);
  }
