#ifndef TIME_MARCHING_KERNEL_H
#define TIME_MARCHING_KERNEL_H

/**
 * @brief  Updates the grid value by 1 at the given point.
 * @note   
 * @param  *u: Grid to be updated.
 * @retval None
 */
void march_kernel(double *un, const double *u0)
{
    un[OPS_ACC0(0, 0)] = u0[OPS_ACC1(0, 0)] + 1;
}

#endif