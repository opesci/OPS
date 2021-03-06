//
// auto-generated by ops.py
//

#define OPS_GPU

int xdim0_apply_stencil;
int xdim1_apply_stencil;

//user function
inline 
void apply_stencil(const ptr_double A, ptr_double Anew, double *error) {
  OPS_ACC(Anew, 0,0) = 0.25f * ( OPS_ACC(A, 1,0) + OPS_ACC(A, -1,0)
      + OPS_ACC(A, 0,-1) + OPS_ACC(A, 0,1));
  *error = fmax( *error, fabs(OPS_ACC(Anew, 0,0)-OPS_ACC(A, 0,0)));
}


void apply_stencil_c_wrapper(
  double *p_a0,
  double *p_a1,
  double *p_a2,
  int x_size, int y_size) {
  double p_a2_0 = p_a2[0];
  #ifdef OPS_GPU
  #pragma acc parallel deviceptr(p_a0,p_a1) reduction(max:p_a2_0)
  #pragma acc loop reduction(max:p_a2_0)
  #endif
  for ( int n_y=0; n_y<y_size; n_y++ ){
    #ifdef OPS_GPU
    #pragma acc loop reduction(max:p_a2_0)
    #endif
    for ( int n_x=0; n_x<x_size; n_x++ ){
      const ptr_double ptr0 = {  p_a0 + n_x*1*1 + n_y*xdim0_apply_stencil*1*1, xdim0_apply_stencil};
      ptr_double ptr1 = {  p_a1 + n_x*1*1 + n_y*xdim1_apply_stencil*1*1, xdim1_apply_stencil};
      apply_stencil( ptr0,
          ptr1, &p_a2_0 );

    }
  }
  p_a2[0] = p_a2_0;
}
