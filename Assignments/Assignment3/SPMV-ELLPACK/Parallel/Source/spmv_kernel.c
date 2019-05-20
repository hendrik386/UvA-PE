#include "spmv_kernel.h"

#include "matrix.h"

void spmv(struct matrix* matrix, float* vector, float* resultVector) {
	matrix_multiply(matrix, vector, resultVector);
}
