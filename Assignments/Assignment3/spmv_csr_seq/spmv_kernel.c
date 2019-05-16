#include "spmv_kernel.h"
#include "stdio.h"

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

   int current_b = 0;

   if (comSR->values == NULL) {
      for (i = 0; i < m; ++i) {
         C[i] = 0;
         for (j = comSR->row_offset[i]; j < comSR->row_offset[i + 1]; ++j)
         {
            C[i] += 1;
         }
         if(comSR->row_offset[i] == nz) {
            break;
         }
         ++current_b;
      }
   }
   else {
      for (i = 0; i < m; ++i) {
         C[i] = 0;
         for (j = comSR->row_offset[i]; j < comSR->row_offset[i + 1]; ++j)
         {
            C[i] += comSR->values[j];
         }
         if(comSR->row_offset[i] == nz) {
            break;
         }
         ++current_b;
      }
   }
}