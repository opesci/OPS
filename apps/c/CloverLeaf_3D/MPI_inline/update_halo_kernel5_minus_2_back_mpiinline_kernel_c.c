//
// auto-generated by ops.py
//

int xdim0_update_halo_kernel5_minus_2_back;
int ydim0_update_halo_kernel5_minus_2_back;
int xdim1_update_halo_kernel5_minus_2_back;
int ydim1_update_halo_kernel5_minus_2_back;


//user function



void update_halo_kernel5_minus_2_back_c_wrapper(
  double * restrict vol_flux_z_p,
  double * restrict mass_flux_z_p,
  const int * restrict fields,
  int x_size, int y_size, int z_size) {
  #pragma omp parallel for
  for ( int n_z=0; n_z<z_size; n_z++ ){
    for ( int n_y=0; n_y<y_size; n_y++ ){
      for ( int n_x=0; n_x<x_size; n_x++ ){
        ptr_double vol_flux_z = { vol_flux_z_p + n_x*1 + n_y * xdim0_update_halo_kernel5_minus_2_back*1 + n_z * xdim0_update_halo_kernel5_minus_2_back * ydim0_update_halo_kernel5_minus_2_back*1, xdim0_update_halo_kernel5_minus_2_back, ydim0_update_halo_kernel5_minus_2_back};
        ptr_double mass_flux_z = { mass_flux_z_p + n_x*1 + n_y * xdim1_update_halo_kernel5_minus_2_back*1 + n_z * xdim1_update_halo_kernel5_minus_2_back * ydim1_update_halo_kernel5_minus_2_back*1, xdim1_update_halo_kernel5_minus_2_back, ydim1_update_halo_kernel5_minus_2_back};
        
  if(fields[FIELD_VOL_FLUX_Z] == 1)  OPS_ACC(vol_flux_z, 0,0,0)  = -OPS_ACC(vol_flux_z, 0,0,2);
  if(fields[FIELD_MASS_FLUX_Z] == 1) OPS_ACC(mass_flux_z, 0,0,0) = -OPS_ACC(mass_flux_z, 0,0,2);

      }
    }
  }
}
