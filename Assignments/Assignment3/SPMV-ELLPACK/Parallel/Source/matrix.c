#include "matrix.h"

#include <stdlib.h>
#include <omp.h>

struct matrix matrix_construct(const int rows, const int columns, const float* matrix) {
	struct matrix result;

	// Set dimensions
	result.rows = rows;
	result.columns = columns;

	// Calculate row_columns_
	result.row_columns_ = malloc(rows * sizeof(int));
	result.maximum_row_columns_ = 0;
	int row;
	int column;
	for(row = 0; row < rows; ++row) {
		for(column = 0; column < columns; ++column) {
			if(matrix[row * columns + column] != 0) {
				result.row_columns_[row] += 1;

				// Calculate maximum value
				const int currentRowColumns = result.row_columns_[row];
				if(currentRowColumns > result.maximum_row_columns_) {
					result.maximum_row_columns_ = currentRowColumns;
				}
			}
		}
	}

	// Allocate and fill data arrays
	result.column_indices_ = (int*) malloc(rows * result.maximum_row_columns_ * sizeof(float));
	result.values_ = (float*) malloc(rows * result.maximum_row_columns_ * sizeof(float));
	for(row = 0; row < rows; ++row) {
		int filledColumns = 0;

		for(column = 0; column < columns; ++column) {
			float value = matrix[row * columns + column];

			if(value != 0) {
				result.values_[row * result.maximum_row_columns_ + filledColumns++] = value;
			}
		}
	}

	return result;
}

void matrix_destroy(struct matrix* matrix) {
	free(matrix->row_columns_);
	free(matrix->column_indices_);
	free(matrix->values_);
}

int matrix_get_value(struct matrix* matrix, const int row, const int column) {
	int internalColumn;

	for(internalColumn = 0; internalColumn < matrix->row_columns_[row]; ++internalColumn) {
		const int index = row * matrix->maximum_row_columns_ + internalColumn;
		const int currentColumn = matrix->column_indices_[index];

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

		for(column = 0; column < matrix->row_columns_[row]; ++column) {
			result_vector[row] += matrix->values_[row * matrix->maximum_row_columns_ + column] * vector[matrix->column_indices_[row * matrix->maximum_row_columns_ + column]];
		}
	}
}
