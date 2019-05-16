#include "spmv_kernel.h"
#include "stdio.h"

#include "omp.h"

#include "iacaMarks.h"

void spmv(int m, int n, float *A, float *B, float *C) {
   int i, j;

   for(i = 0; i < m; i++) {
      C[i] = 0;
      for(j = 0; j < n; j++) {
         C[i] += A[i * n + j] * B[j];
      }
   }
}

void spmv_csr(int m, int n, int nz, struct csr *comSR, float *B, float *C) {
   int i, j;
   omp_set_num_threads(4);
   if (comSR->values == NULL) {
      #pragma omp parallel for private(i, j)
      for (i = 0; i < m; ++i) {
         C[i] = 0;
         for (j = comSR->row_offset[i]; j < comSR->row_offset[i + 1]; ++j)
         {
            C[i] += B[i];
         }
      }
   }
   else {
      #pragma omp parallel for private(i, j)
      for (i = 0; i < m; ++i) {
         C[i] = 0;
         for (j = comSR->row_offset[i]; j < comSR->row_offset[i + 1]; ++j)
         {
            C[i] += comSR->values[j] * B[i];
         }
      }
   }
}