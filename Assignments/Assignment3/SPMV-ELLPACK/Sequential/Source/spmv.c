/* SpMV: this file contains the I/O functions used to read and write matrices
 * in the Market Matrix format(see
 * https://math.nist.gov/MatrixMarket/formats.html#MMformat), using the
 * functions in mmio.c in its turn.
 * A vector of the appropriate size is generated and multiplied with the matrix.
 * There are also functions to generate your own matrices.
 * The reading also supports the "is_pattern" flag from the Matrix Market format. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mmio.h"
#include "spmv_kernel.h"

#include "matrix.h"

#define N  512
#define M  512

#define REP 1000

void generate_mat(int m, int n, float* A) {
	int i;

	for(i = 0; i < (m * n); i++) {
		A[i] = 1;
	} //i/10;

}

struct matrix read_sparse(FILE* file, int rows, int columns, int dimensions, const int is_pattern) {
	/* NOTE: when reading in doubles, ANSI C requires the use of the "l"  */
	/*   specifier as in "%lg", "%lf", "%le", otherwise errors will occur */
	/*  (ANSI C X3.159-1989, Sec. 4.9.6.2, p. 136 lines 13-15)            */

	// Load the full matrix
	float* fullMatrix = (float*) calloc(rows * columns, sizeof(float));
	int index;
	int row;
	int column;
	float value;
	for(index = 0; index < dimensions; ++index) {
		if(is_pattern) {
			fscanf(file, "%d %d\n", &row, &column);
		} else {
			fscanf(file, "%d %d %f\n", &row, &column, &value);
		}

		fullMatrix[(row - 1) * columns + column - 1] = is_pattern
			? 1.0f
			: value;
	}

	// Create and return sparse matrix
	struct matrix result = matrix_construct(rows, columns, fullMatrix);

	free(fullMatrix);

	return result;
}

void write_sparse(FILE* file, int m, int p, const float* C) {
	int i, nz = 0;
	MM_typecode matcode;

	for(i = 0; i < m * p; i++) {
		if(C[i] != 0.0) {
			nz++;
		}
	}

	mm_initialize_typecode(&matcode);
	mm_set_matrix(&matcode);
	mm_set_coordinate(&matcode);
	mm_set_real(&matcode);

	mm_write_banner(file, matcode);
	mm_write_mtx_crd_size(file, m, p, nz);

	for(i = 0; i < m * p; i++) {
		if(C[i] != 0.0) {
			fprintf(file, "%d %d %f\n", i / p + 1, i % p + 1, C[i]);
		}
	}

}

void write_vector(FILE* file, int m, const float* C) {
	int i;

	for(i = 0; i < m; i++) {
		fprintf(file, "%f\n", C[i]);
	}
}

void read_dense(FILE* file, int rows, int columns, float* matrix) {
	int row, column;

	for(row = 0; row < rows; row++) {
		for(column = 0; column < columns; column++) {
			fscanf(file, "%f ", &matrix[row * columns + column]);
			//	printf("%20.19f \columns", matrix[row*(*columns)+column]);
		}
	}
}

int read_mat(int* m, int* n, int* nzA, FILE* fa, int* is_pattern) {
	MM_typecode ta;
	int ret_code;

	if(mm_read_banner(fa, &ta) != 0) {
		printf("Could not process Matrix Market banner for A.\n");
		return -3;
	}

	if(mm_is_pattern(ta)) {
		*is_pattern = 1;
	}

	if(mm_is_complex(ta)) {
		return -6;
	}

	if(mm_is_matrix(ta) && mm_is_sparse(ta)) {
		if((ret_code = mm_read_mtx_crd_size(fa, m, n, nzA)) != 0) {
			return -10;
		}
	} else if(mm_is_matrix(ta) && mm_is_array(ta)) {
		*nzA = 0;
		if((ret_code = mm_read_mtx_array_size(fa, m, n)) != 0) {
			return -11;
		}

	} else {
		return -8;
	}

	return 0;
}

int main(int argc, char** argv) {
	int rows;
	int columns;
	int dimensions = 0;
	int is_pattern = 0;
	FILE* inputFile;

	#ifdef GENERATE
	rows = M;
	columns = N;
	#else
	if(argc < 3) {
		fprintf(stderr, "Usage: %s [matrix-market-filename] [result-vector-filename]\n", argv[0]);
		exit(1);
	} else {
		if((inputFile = fopen(argv[1], "rt")) == NULL) {
			exit(1);
		}
		int errorCode = read_mat(&rows, &columns, &dimensions, inputFile, &is_pattern);
		if(errorCode == -15) {
			printf("Matrices are incompatible! \n");
			fclose(inputFile);
			exit(1);
		}
	}
	#endif

	if(argc == 4) {
		is_pattern = atoi(argv[3]);
	}

	struct matrix matrix;
	float* vector = (float*) calloc(columns, sizeof(float));
	float* result_vector = (float*) calloc(rows, sizeof(float));

	#ifdef GENERATE
	generate_mat(rows, columns, matrix);
	generate_mat(columns, 1, vector);
	#else
	if(dimensions > 0) {
		matrix = read_sparse(inputFile, rows, columns, dimensions, is_pattern);
	} else {
		//read_dense(inputFile, rows, columns, matrix);
	}
	generate_mat(columns, 1, vector);
	fclose(inputFile);
	#endif

	#ifdef TIMING
	//naive implementation
	struct timeval before;
	gettimeofday(&before, NULL);
	#endif

	int repetition;
	for(repetition = 0; repetition < REP; repetition++) {
		/* Call the SpMV kernel. */
		spmv(&matrix, vector, result_vector);
	}

	#ifdef TIMING
	struct timeval after;
	gettimeofday(&after, NULL);

	printf("Reference code: %10.6f seconds \n", ((after.tv_sec + (after.tv_usec / 1000000.0)) - (before.tv_sec + (before.tv_usec / 1000000.0))) / REP);
	#endif

	FILE* outputFile;
	if((outputFile = fopen(argv[2], "wt")) == NULL) {
		exit(3);
	}
	// write_sparse(outputFile,columns,rows,result_vector);
	write_vector(outputFile, rows, result_vector);
	fclose(outputFile);

	matrix_destroy(&matrix);
	free(vector);
	free(result_vector);
}

