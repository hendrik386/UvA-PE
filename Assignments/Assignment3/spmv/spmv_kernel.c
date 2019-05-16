#include "spmv_kernel.h"


void spmv(int m, int n, float *A, float *B, float *C) {
   int i, j;

   for(i=0; i<m; i++) {
      C[i]=0;
      for(j=0; j<n; j++) {
         C[i] += A[i*n+j]*B[j];
      }
   }
}
