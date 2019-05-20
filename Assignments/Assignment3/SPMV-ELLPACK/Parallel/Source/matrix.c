#include "matrix.h"

#include <stdlib.h>
#include <omp.h>

struct matrix matrix_construct(const int rows, const int columns, const float* matrix) {
	struct matrix result;

	// Set dimensions
	result.rows = rows;
	result.columns = columns;

	// Calculate rowColumns_
	result.rowColumns_ = malloc(rows * sizeof(int));
	result.maximumRowColumns_ = 0;
	int row;
	int column;
	for(row = 0; row < rows; ++row) {
		for(column = 0; column < columns; ++column) {
			if(matrix[row * columns + column] != 0) {
				result.rowColumns_[row] += 1;

				// Calculate maximum value
				const int currentRowColumns = result.rowColumns_[row];
				if(currentRowColumns > result.maximumRowColumns_) {
					result.maximumRowColumns_ = currentRowColumns;
				}
			}
		}
	}

	// Allocate and fill data arrays
	result.columnIndices_ = (int*) malloc(rows * result.maximumRowColumns_ * sizeof(float));
	result.values_ = (float*) malloc(rows * result.maximumRowColumns_ * sizeof(float));
	for(row = 0; row < rows; ++row) {
		int filledColumns = 0;

		for(column = 0; column < columns; ++column) {
			float value = matrix[row * columns + column];

			if(value != 0) {
				result.values_[row * result.maximumRowColumns_ + filledColumns++] = value;
			}
		}
	}

	return result;
}

void matrix_destroy(struct matrix* matrix) {
	free(matrix->rowColumns_);
	free(matrix->columnIndices_);
	free(matrix->values_);
}

int matrix_get_value(struct matrix* matrix, const int row, const int column) {
	int internalColumn;

	for(internalColumn = 0; internalColumn < matrix->rowColumns_[row]; ++internalColumn) {
		const int index = row * matrix->maximumRowColumns_ + internalColumn;
		const int currentColumn = matrix->columnIndices_[index];

		if(currentColumn == column) {
			return matrix->values_[index];
		} else if(currentColumn > column) {
			break;
		}
	}

	return 0;
}

void matrix_multiply(const struct matrix* matrix, const float* vector, float* result_vector) {
	omp_set_num_threads(4);

	int row;
	int column;

	#pragma omp parallel for
	for(row = 0; row < matrix->rows; ++row) {
		result_vector[row] = 0;

		for(column = 0; column < matrix->rowColumns_[row]; ++column) {
			result_vector[row] += matrix->values_[row * matrix->maximumRowColumns_ + column] * vector[matrix->columnIndices_[row * matrix->maximumRowColumns_ + column]];
		}
	}
}
