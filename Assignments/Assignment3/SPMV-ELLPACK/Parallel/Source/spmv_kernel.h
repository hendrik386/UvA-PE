#ifndef SPMV_KERNEL_H
#define SPMV_KERNEL_H

struct matrix;

void spmv(struct matrix* matrix, float* vector, float* resultVector);

#endif
