#ifndef SPMV_KERNEL_H
#define SPMV_KERNEL_H

struct csr{
    int *row_offset;
    int *column_indices;
    float *values;
};

void spmv(int m, int n, float *A, float *B, float *C);
void spmv_csr(int m, int n, int nz, struct csr *comSR, float *B, float *C);

#endif
