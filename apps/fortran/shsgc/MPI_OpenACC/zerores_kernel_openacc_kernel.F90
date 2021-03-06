!
! auto-generated by ops_fortran.py
!
MODULE ZERORES_KERNEL_MODULE
USE OPS_FORTRAN_DECLARATIONS
USE OPS_FORTRAN_RT_SUPPORT

USE OPS_CONSTANTS
USE ISO_C_BINDING

INTEGER(KIND=4) xdim1
#define OPS_ACC1(x) (x+1)
INTEGER(KIND=4) xdim2
#define OPS_ACC2(x) (x+1)
INTEGER(KIND=4) xdim3
#define OPS_ACC3(x) (x+1)


contains

!$ACC ROUTINE(zerores_kernel) SEQ
!user function
subroutine zerores_kernel(rho_res, rhou_res, rhoE_res)

  real (kind=8) , DIMENSION(1) :: rho_res, rhou_res, rhoE_res

    rho_res(OPS_ACC1(0))= 0.0_8
    rhou_res(OPS_ACC2(0))= 0.0_8
    rhoE_res(OPS_ACC3(0))= 0.0_8

end subroutine

#undef OPS_ACC1
#undef OPS_ACC2
#undef OPS_ACC3



subroutine zerores_kernel_wrap( &
& opsDat1Local, &
& opsDat2Local, &
& opsDat3Local, &
& dat1_base, &
& dat2_base, &
& dat3_base, &
& start, &
& end )
  IMPLICIT NONE
  real(8) :: opsDat1Local(*)
  real(8) :: opsDat2Local(*)
  real(8) :: opsDat3Local(*)
  integer :: dat1_base
  integer :: dat2_base
  integer :: dat3_base
  integer(4) start(1)
  integer(4) end(1)
  integer n_x


  !$acc parallel deviceptr(opsDat1Local,opsDat2Local,opsDat3Local)  
  !$acc loop 
  DO n_x = 1, end(1)-start(1)+1
    call zerores_kernel( &
    & opsDat1Local(dat1_base+(n_x-1)*1), &
    & opsDat2Local(dat2_base+(n_x-1)*1), &
    & opsDat3Local(dat3_base+(n_x-1)*1) )
  END DO
  !$acc end parallel

end subroutine

!host subroutine
subroutine zerores_kernel_host( userSubroutine, block, dim, range, &
& opsArg1, &
& opsArg2, &
& opsArg3)
  IMPLICIT NONE
  character(kind=c_char,len=*), INTENT(IN) :: userSubroutine
  type ( ops_block ), INTENT(IN) :: block
  integer(kind=4), INTENT(IN):: dim
  integer(kind=4)   , DIMENSION(dim), INTENT(IN) :: range
  real(kind=8) t1,t2,t3
  real(kind=4) transfer_total, transfer

  type ( ops_arg )  , INTENT(IN) :: opsArg1
  real(8), DIMENSION(:), POINTER :: opsDat1Local
  integer(kind=4) :: opsDat1Cardinality
  integer(kind=4), POINTER, DIMENSION(:)  :: dat1_size
  integer(kind=4) :: dat1_base

  type ( ops_arg )  , INTENT(IN) :: opsArg2
  real(8), DIMENSION(:), POINTER :: opsDat2Local
  integer(kind=4) :: opsDat2Cardinality
  integer(kind=4), POINTER, DIMENSION(:)  :: dat2_size
  integer(kind=4) :: dat2_base

  type ( ops_arg )  , INTENT(IN) :: opsArg3
  real(8), DIMENSION(:), POINTER :: opsDat3Local
  integer(kind=4) :: opsDat3Cardinality
  integer(kind=4), POINTER, DIMENSION(:)  :: dat3_size
  integer(kind=4) :: dat3_base

  integer n_x
  integer start(1)
  integer end(1)
  integer(kind=4) :: n

  type ( ops_arg ) , DIMENSION(3) :: opsArgArray

  opsArgArray(1) = opsArg1
  opsArgArray(2) = opsArg2
  opsArgArray(3) = opsArg3

  call setKernelTime(2,userSubroutine//char(0),0.0_8,0.0_8,0.0_4,0)
  call ops_timers_core(t1)

#ifdef OPS_MPI
  IF (getRange(block, start, end, range) < 0) THEN
    return
  ENDIF
#else
  DO n = 1, 1
    start(n) = range(2*n-1)
    end(n) = range(2*n);
  END DO
#endif

  call c_f_pointer(getDatSizeFromOpsArg(opsArg1),dat1_size,(/dim/))
  xdim1 = dat1_size(1)
  opsDat1Cardinality = opsArg1%dim * xdim1
  dat1_base = getDatBaseFromOpsArg1D(opsArg1,start,1)
  call c_f_pointer(opsArg1%data_d,opsDat1Local,(/opsDat1Cardinality/))

  call c_f_pointer(getDatSizeFromOpsArg(opsArg2),dat2_size,(/dim/))
  xdim2 = dat2_size(1)
  opsDat2Cardinality = opsArg2%dim * xdim2
  dat2_base = getDatBaseFromOpsArg1D(opsArg2,start,1)
  call c_f_pointer(opsArg2%data_d,opsDat2Local,(/opsDat2Cardinality/))

  call c_f_pointer(getDatSizeFromOpsArg(opsArg3),dat3_size,(/dim/))
  xdim3 = dat3_size(1)
  opsDat3Cardinality = opsArg3%dim * xdim3
  dat3_base = getDatBaseFromOpsArg1D(opsArg3,start,1)
  call c_f_pointer(opsArg3%data_d,opsDat3Local,(/opsDat3Cardinality/))

  call ops_H_D_exchanges_device(opsArgArray,3)
  call ops_halo_exchanges(opsArgArray,3,range)
  call ops_H_D_exchanges_device(opsArgArray,3)

  call ops_timers_core(t2)

  call zerores_kernel_wrap( &
  & opsDat1Local, &
  & opsDat2Local, &
  & opsDat3Local, &
  & dat1_base, &
  & dat2_base, &
  & dat3_base, &
  & start, &
  & end )

  call ops_timers_core(t3)
  call ops_set_dirtybit_device(opsArgArray, 3)
  call ops_set_halo_dirtybit3(opsArg1,range)
  call ops_set_halo_dirtybit3(opsArg2,range)
  call ops_set_halo_dirtybit3(opsArg3,range)

  !Timing and data movement
  transfer_total = 0.0_4
  call ops_compute_transfer(1, start, end, opsArg1,transfer)
  transfer_total = transfer_total + transfer
  call ops_compute_transfer(1, start, end, opsArg2,transfer)
  transfer_total = transfer_total + transfer
  call ops_compute_transfer(1, start, end, opsArg3,transfer)
  transfer_total = transfer_total + transfer
  call setKernelTime(2,userSubroutine,t3-t2,t2-t1,transfer_total,1)
end subroutine
END MODULE
