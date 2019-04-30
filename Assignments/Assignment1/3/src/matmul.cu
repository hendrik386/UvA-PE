#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <cuda.h>
#include <cuda_runtime_api.h>
#include <device_launch_parameters.h>
#include "mmio.h"

#define N  512
#define M  512
#define P  512

#define REP 50

//region CPU

void matrix_mult(int left_rows, int shared_dimensions, int right_columns, float* left, float* right, float* result) {
	int row;
	int column;
	int cell;

	for(row = 0; row < left_rows; row++) {
		for(column = 0; column < right_columns; column++) {
			result[row * right_columns + column] = 0;

			for(cell = 0; cell < shared_dimensions; cell++) {
				result[row * right_columns + column] += left[row * shared_dimensions + cell] * right[cell * right_columns + column];
			}
		}
	}
}

void generate_mat(int left_rows, int shared_dimensions, int right_columns, float* left, float* right) {
	int cell;

	for(cell = 0; cell < (left_rows * shared_dimensions); cell++) {
		left[cell] = 1;
	} //cell/10;

	for(cell = 0; cell < (shared_dimensions * right_columns); cell++) {
		right[cell] = 1; //cell/5;
	}
}

void read_sparse(FILE* file, int rows, int columns, int nz, float* matrix) {
	int i;
	int row;
	int column;
	float value;

	/* NOTE: when reading in doubles, ANSI C requires the use of the "l"  */
	/*   specifier as in "%lg", "%lf", "%le", otherwise errors will occur */
	/*  (ANSI C X3.159-1989, Sec. 4.9.6.2, p. 136 lines 13-15)            */

	for(i = 0; i < nz; i++) {
		fscanf(file, "%d %d %f\n", &row, &column, &value);

		matrix[(row - 1) * columns + column - 1] = value;   /* adjust from 1-based to 0-based */
	}

}

void write_sparse(FILE* file, int rows, int columns, const float* matrix) {
	int i;
	int nz = 0;
	MM_typecode matrix_banner;

	for(i = 0; i < rows * columns; i++) {
		if(matrix[i] != 0.0) {
			nz++;
		}
	}

	mm_initialize_typecode(&matrix_banner);
	mm_set_matrix(&matrix_banner);
	mm_set_coordinate(&matrix_banner);
	mm_set_real(&matrix_banner);

	mm_write_banner(file, matrix_banner);
	mm_write_mtx_crd_size(file, rows, columns, nz);

	for(i = 0; i < rows * columns; i++) {
		if(matrix[i] != 0.0) {
			fprintf(file, "%d %d %f\n", i / columns + 1, i % columns + 1, matrix[i]);
		}
	}

}

void read_dense(FILE* matrix_file, int rows, int columns, float* matrix) {
	int row;
	int column;

	for(row = 0; row < rows; row++) {
		for(column = 0; column < columns; column++) {
			fscanf(matrix_file, "%f ", &matrix[row * columns + column]);

			//	printf("%20.19f \columns", matrix[row*(*columns)+column]);
		}
	}
}

int read_mat(int* left_rows, int* shared_dimensions, int* right_columns, int* nzA, int* nzB, FILE* left_file, FILE* right_file) {
	MM_typecode left_banner;
	MM_typecode right_banner;
	int return_code;
	int n1;

	if(mm_read_banner(left_file, &left_banner) != 0) {
		printf("Could not process Matrix Market banner for A.\n");

		return -3;
	}
	if(mm_read_banner(right_file, &right_banner) != 0) {
		printf("Could not process Matrix Market banner for B.\n");

		return -4;
	}

	if(mm_is_complex(left_banner)) {
		return -6;
	}
	if(mm_is_complex(right_banner)) {
		return -7;
	}

	if(mm_is_matrix(left_banner) && mm_is_sparse(left_banner)) {
		if((return_code = mm_read_mtx_crd_size(left_file, left_rows, shared_dimensions, nzA)) != 0) {
			return -10;
		}
	} else if(mm_is_matrix(left_banner) && mm_is_array(left_banner)) {
		*nzA = 0;
		if((return_code = mm_read_mtx_array_size(left_file, left_rows, shared_dimensions)) != 0) {
			return -11;
		}

	} else {
		return -8;
	}

	if(mm_is_matrix(right_banner) && mm_is_sparse(right_banner)) {
		if((return_code = mm_read_mtx_crd_size(right_file, &n1, right_columns, nzB)) != 0) {
			return -10;
		}
	} else if(mm_is_matrix(right_banner) && mm_is_array(right_banner)) {
		*nzB = 0;
		if((return_code = mm_read_mtx_array_size(right_file, &n1, right_columns)) != 0) {
			return -11;
		}

	} else {
		return -9;
	}

	if(*shared_dimensions != n1) {
		return -15;
	}

	return 0;
	/* find out size of sparse matrix .... */
}

//endregion

//region GPU

float* device_left;

float* device_right;

float* device_result;

__global__ void gpu_matrix_mult(int left_rows, int shared_dimensions, int right_columns, float* left, float* right, float* result) {
	// Get position in the result matrix
	int row = blockIdx.y * blockDim.y + threadIdx.y;
	int column = blockIdx.x * blockDim.x + threadIdx.x;

	// Check if we're inside the bounds of the result matrix
	if(row < left_rows && column < right_columns) {
		// Convert coordinates to 1D index
		int index = row * right_columns + column;

		// Initialize result value
		result[index] = 0;

		// Perform multiplication operation
		int cell;
		for(cell = 0; cell < shared_dimensions; cell++) {
			result[index] += left[row * shared_dimensions + cell] * right[cell * right_columns + column];
		}
	}
}

void output_gpu_info() {
	int runtimeVersion = 0;
	int driverVersion = 0;
	cudaRuntimeGetVersion(&runtimeVersion);
	cudaDriverGetVersion(&driverVersion);

	printf("CUDA runtime version: %d\n", runtimeVersion);
	printf("CUDA driver version: %d\n", driverVersion);
}

static void checkCudaCall(cudaError_t result) {
	if(result != cudaSuccess) {
		printf("CUDA error %s: %s\n", cudaGetErrorName(result), cudaGetErrorString(result));

		exit(1);
	}
}

//endregion

int main(int argument_count, char** argument_values) {
	#ifdef TIMING
	struct timeval before;
	struct timeval after;
	#endif

	int nzA = 0;
	int nzB = 0;
	FILE* left_file;
	FILE* right_file;

	int left_rows;
	int shared_dimensions;
	int right_columns;
	#ifdef GENERATE
	left_rows = M;
	shared_dimensions = N;
	right_columns = P;
	#else
	if(argument_count < 3) {
		fprintf(stderr, "Usage: %s [martix1] [matrix2] [resultmatrix] \n", argument_values[0]);
		exit(1);
	} else {
		if((left_file = fopen(argument_values[1], "rt")) == NULL) {
			exit(1);
		}

		if((right_file = fopen(argument_values[2], "rt")) == NULL) {
			exit(2);
		}

		int error_code = read_mat(&left_rows, &shared_dimensions, &right_columns, &nzA, &nzB, left_file, right_file);
		if(error_code == -15) {
			printf("Matrices are incompatible! \n");
			fclose(left_file);
			fclose(right_file);
			exit(1);
		}
	}
	#endif

	float* left = (float*) calloc(left_rows * shared_dimensions, sizeof(float));
	if(left == NULL) {
		printf("Out of memory left! \n");
		exit(1);
	}

	float* right = (float*) calloc(shared_dimensions * right_columns, sizeof(float));
	if(right == NULL) {
		printf("Out of memory right! \n");
		exit(1);
	}

	#ifdef GENERATE
	generate_mat(left_rows, shared_dimensions, right_columns, left, right);
	#else
	if(nzA > 0) {
		read_sparse(left_file, left_rows, shared_dimensions, nzA, left);
	} else {
		read_dense(left_file, left_rows, shared_dimensions, left);
	}

	if(nzB > 0) {
		read_sparse(right_file, shared_dimensions, right_columns, nzB, right);
	} else {
		read_dense(right_file, shared_dimensions, right_columns, right);
	}

	fclose(left_file);
	fclose(right_file);
	#endif

	float* result = (float*) calloc(left_rows * right_columns, sizeof(float));
	if(result == NULL) {
		printf("Out of memory C1! \n");
		exit(1);
	}
	// C2 = (float *)calloc(N*P,sizeof(float));
	// if (C2==NULL) {printf("Out of memory C2! \n"); exit(1);}

	// Initialize cuda
	output_gpu_info();
	dim3 block_size(16, 16);
	dim3 grid_size((right_columns + block_size.x - 1) / block_size.x, (left_rows + block_size.y - 1) / block_size.y);
	printf("Grid size: (%d, %d, %d)\n", grid_size.x, grid_size.y, grid_size.z);
	printf("Block size: (%d, %d, %d)\n", block_size.x, block_size.y, block_size.z);
	cudaMalloc((void**) &device_left, left_rows * shared_dimensions * sizeof(float));
	cudaMalloc((void**) &device_right, shared_dimensions * right_columns * sizeof(float));
	cudaMalloc((void**) &device_result, left_rows * right_columns * sizeof(float));
	cudaMemcpy(device_left, left, left_rows * shared_dimensions * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(device_right, right, shared_dimensions * right_columns * sizeof(float), cudaMemcpyHostToDevice);
	cudaMemcpy(device_result, result, left_rows * right_columns * sizeof(float), cudaMemcpyHostToDevice);

	// Naive implementation
	#ifdef TIMING
	gettimeofday(&before, NULL);
	#endif

	int r;
	for(r = 0; r < REP; r++) {
		gpu_matrix_mult << < grid_size, block_size >> > (left_rows, shared_dimensions, right_columns, device_left, device_right, device_result);
	}
	cudaDeviceSynchronize();
	checkCudaCall(cudaGetLastError());

	#ifdef TIMING
	gettimeofday(&after, NULL);
	printf("Reference code: %10.6f seconds \n", ((after.tv_sec + (after.tv_usec / 1000000.0)) - (before.tv_sec + (before.tv_usec / 1000000.0))) / REP);
	#endif

	// Retrieve GPU data and clean up
	cudaMemcpy(left, device_left, left_rows * shared_dimensions * sizeof(float), cudaMemcpyDeviceToHost);
	cudaMemcpy(right, device_right, shared_dimensions * right_columns * sizeof(float), cudaMemcpyDeviceToHost);
	cudaMemcpy(result, device_result, left_rows * right_columns * sizeof(float), cudaMemcpyDeviceToHost);
	cudaFree(device_left);
	cudaFree(device_right);
	cudaFree(device_result);

	FILE* result_file;
	#ifdef GENERATE
	if ((result_file = fopen("gen_result.mtx", "wt")) == NULL) {
		exit(3);
	}
	#else
	if((result_file = fopen(argument_values[3], "wt")) == NULL) {
		exit(3);
	}
	#endif
	write_sparse(result_file, left_rows, right_columns, result);
	fclose(result_file);

	free(left);
	free(right);
	free(result);
	// free(C2);
}

