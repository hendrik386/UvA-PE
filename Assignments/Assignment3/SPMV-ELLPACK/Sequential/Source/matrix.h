#ifndef ASSIGNMENTS_MATRIX_H
#define ASSIGNMENTS_MATRIX_H

struct matrix {
	int rows;
	int columns;

	int* rowColumns_;
	int maximumRowColumns_;
	int* columnIndices_;
	float* values_;

};

struct matrix matrix_construct(const int rows, const int columns, const float* matrix);

void matrix_destroy(struct matrix* matrix);

int matrix_get_value(struct matrix* matrix, const int row, const int column);

void matrix_multiply(const struct matrix* matrix, const float* vector, float* result_vector);

#endif
