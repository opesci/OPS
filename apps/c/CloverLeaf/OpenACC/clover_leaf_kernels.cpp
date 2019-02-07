//
// auto-generated by ops.py//

#include "./OpenACC/clover_leaf_common.h"

#include <openacc.h>

void ops_init_backend() {acc_set_device_num(ops_get_proc()%acc_get_num_devices(acc_device_nvidia),acc_device_nvidia); ops_device_initialised_externally = 1;}

void ops_decl_const_char(int dim, char const *type,
int size, char *dat, char const *name){
  if (!strcmp(name,"g_small")) {
    g_small = *(double*)dat;
  }
  else
  if (!strcmp(name,"g_big")) {
    g_big = *(double*)dat;
  }
  else
  if (!strcmp(name,"dtc_safe")) {
    dtc_safe = *(double*)dat;
  }
  else
  if (!strcmp(name,"dtu_safe")) {
    dtu_safe = *(double*)dat;
  }
  else
  if (!strcmp(name,"dtv_safe")) {
    dtv_safe = *(double*)dat;
  }
  else
  if (!strcmp(name,"dtdiv_safe")) {
    dtdiv_safe = *(double*)dat;
  }
  else
  if (!strcmp(name,"field")) {
    field = *(field_type*)dat;
  }
  else
  if (!strcmp(name,"grid")) {
    grid = *(grid_type*)dat;
  }
  else
  if (!strcmp(name,"number_of_states")) {
    number_of_states = *(int*)dat;
  }
  else
  if (!strcmp(name,"states")) {
    states = (state_type*)dat;
  }
  else
  if (!strcmp(name,"g_circ")) {
    g_circ = *(int*)dat;
  }
  else
  if (!strcmp(name,"g_point")) {
    g_point = *(int*)dat;
  }
  else
  if (!strcmp(name,"g_rect")) {
    g_rect = *(int*)dat;
  }
  else
  if (!strcmp(name,"dt")) {
    dt = *(double*)dat;
  }
  else
  {
    printf("error: unknown const name\n"); exit(1);
  }
}

//user kernel files
#include "revert_kernel_openacc_kernel.cpp"
#include "reset_field_kernel1_openacc_kernel.cpp"
#include "reset_field_kernel2_openacc_kernel.cpp"
#include "ideal_gas_kernel_openacc_kernel.cpp"
#include "PdV_kernel_predict_openacc_kernel.cpp"
#include "PdV_kernel_nopredict_openacc_kernel.cpp"
#include "accelerate_kernel_openacc_kernel.cpp"
#include "advec_cell_kernel1_xdir_openacc_kernel.cpp"
#include "advec_cell_kernel2_xdir_openacc_kernel.cpp"
#include "advec_cell_kernel3_xdir_openacc_kernel.cpp"
#include "advec_cell_kernel4_xdir_openacc_kernel.cpp"
#include "advec_cell_kernel1_ydir_openacc_kernel.cpp"
#include "advec_cell_kernel2_ydir_openacc_kernel.cpp"
#include "advec_cell_kernel3_ydir_openacc_kernel.cpp"
#include "advec_cell_kernel4_ydir_openacc_kernel.cpp"
#include "advec_mom_kernel_x1_openacc_kernel.cpp"
#include "advec_mom_kernel_y1_openacc_kernel.cpp"
#include "advec_mom_kernel_x2_openacc_kernel.cpp"
#include "advec_mom_kernel_y2_openacc_kernel.cpp"
#include "advec_mom_kernel_mass_flux_x_openacc_kernel.cpp"
#include "advec_mom_kernel_post_pre_advec_x_openacc_kernel.cpp"
#include "advec_mom_kernel1_x_nonvector_openacc_kernel.cpp"
#include "advec_mom_kernel2_x_openacc_kernel.cpp"
#include "advec_mom_kernel_mass_flux_y_openacc_kernel.cpp"
#include "advec_mom_kernel_post_pre_advec_y_openacc_kernel.cpp"
#include "advec_mom_kernel1_y_nonvector_openacc_kernel.cpp"
#include "advec_mom_kernel2_y_openacc_kernel.cpp"
#include "calc_dt_kernel_openacc_kernel.cpp"
#include "calc_dt_kernel_min_openacc_kernel.cpp"
#include "calc_dt_kernel_get_openacc_kernel.cpp"
#include "calc_dt_kernel_print_openacc_kernel.cpp"
#include "field_summary_kernel_openacc_kernel.cpp"
#include "flux_calc_kernelx_openacc_kernel.cpp"
#include "flux_calc_kernely_openacc_kernel.cpp"
#include "viscosity_kernel_openacc_kernel.cpp"
#include "initialise_chunk_kernel_xx_openacc_kernel.cpp"
#include "initialise_chunk_kernel_yy_openacc_kernel.cpp"
#include "initialise_chunk_kernel_x_openacc_kernel.cpp"
#include "initialise_chunk_kernel_y_openacc_kernel.cpp"
#include "initialise_chunk_kernel_cellx_openacc_kernel.cpp"
#include "initialise_chunk_kernel_celly_openacc_kernel.cpp"
#include "initialise_chunk_kernel_volume_openacc_kernel.cpp"
#include "generate_chunk_kernel_openacc_kernel.cpp"
#include "update_halo_kernel1_b2_openacc_kernel.cpp"
#include "update_halo_kernel1_b1_openacc_kernel.cpp"
#include "update_halo_kernel1_t2_openacc_kernel.cpp"
#include "update_halo_kernel1_t1_openacc_kernel.cpp"
#include "update_halo_kernel1_l2_openacc_kernel.cpp"
#include "update_halo_kernel1_l1_openacc_kernel.cpp"
#include "update_halo_kernel1_r2_openacc_kernel.cpp"
#include "update_halo_kernel1_r1_openacc_kernel.cpp"
#include "update_halo_kernel2_xvel_plus_4_a_openacc_kernel.cpp"
#include "update_halo_kernel2_xvel_plus_2_a_openacc_kernel.cpp"
#include "update_halo_kernel2_xvel_plus_4_b_openacc_kernel.cpp"
#include "update_halo_kernel2_xvel_plus_2_b_openacc_kernel.cpp"
#include "update_halo_kernel2_xvel_minus_4_a_openacc_kernel.cpp"
#include "update_halo_kernel2_xvel_minus_2_a_openacc_kernel.cpp"
#include "update_halo_kernel2_xvel_minus_4_b_openacc_kernel.cpp"
#include "update_halo_kernel2_xvel_minus_2_b_openacc_kernel.cpp"
#include "update_halo_kernel2_yvel_minus_4_a_openacc_kernel.cpp"
#include "update_halo_kernel2_yvel_minus_2_a_openacc_kernel.cpp"
#include "update_halo_kernel2_yvel_minus_4_b_openacc_kernel.cpp"
#include "update_halo_kernel2_yvel_minus_2_b_openacc_kernel.cpp"
#include "update_halo_kernel2_yvel_plus_4_a_openacc_kernel.cpp"
#include "update_halo_kernel2_yvel_plus_2_a_openacc_kernel.cpp"
#include "update_halo_kernel2_yvel_plus_4_b_openacc_kernel.cpp"
#include "update_halo_kernel2_yvel_plus_2_b_openacc_kernel.cpp"
#include "update_halo_kernel3_plus_4_a_openacc_kernel.cpp"
#include "update_halo_kernel3_plus_2_a_openacc_kernel.cpp"
#include "update_halo_kernel3_plus_4_b_openacc_kernel.cpp"
#include "update_halo_kernel3_plus_2_b_openacc_kernel.cpp"
#include "update_halo_kernel3_minus_4_a_openacc_kernel.cpp"
#include "update_halo_kernel3_minus_2_a_openacc_kernel.cpp"
#include "update_halo_kernel3_minus_4_b_openacc_kernel.cpp"
#include "update_halo_kernel3_minus_2_b_openacc_kernel.cpp"
#include "update_halo_kernel4_minus_4_a_openacc_kernel.cpp"
#include "update_halo_kernel4_minus_2_a_openacc_kernel.cpp"
#include "update_halo_kernel4_minus_4_b_openacc_kernel.cpp"
#include "update_halo_kernel4_minus_2_b_openacc_kernel.cpp"
#include "update_halo_kernel4_plus_4_a_openacc_kernel.cpp"
#include "update_halo_kernel4_plus_2_a_openacc_kernel.cpp"
#include "update_halo_kernel4_plus_4_b_openacc_kernel.cpp"
#include "update_halo_kernel4_plus_2_b_openacc_kernel.cpp"
