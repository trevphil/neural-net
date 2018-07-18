#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "matrix.h"

Matrix * make_matrix(int n_rows, int n_cols) {
    Matrix *matrix = malloc(sizeof(Matrix));
    matrix->rows = n_rows;
    matrix->cols = n_cols;
    double **data = malloc(sizeof(double *) * n_rows);
	for (int row = 0; row < n_rows; row++) {
		data[row] = calloc(n_cols, sizeof(double));
	}
	matrix->data = data;
    return matrix;
}

void free_matrix(Matrix *m) {
	free(m);
	m = NULL;
}

Matrix * copy_matrix(Matrix *m) {
	Matrix *x = make_matrix(m->rows, m->cols);
	for (int row = 0; row < m->rows; row++) {
		for (int col = 0; col < m->cols; col++) {
			matrix_set(x, row, col, matrix_get(m, row, col));
		}
	}
	return x;
}

double matrix_get(Matrix *m, int row, int col) {
	assert(m);
	assert(row >= 0 && row < m->rows);
	assert(col >= 0 && col < m->cols);
	return m->data[row][col];
}

void matrix_set(Matrix *m, int row, int col, double val) {
	if (!m) { return; }
	assert(row >= 0 && row < m->rows);
	assert(col >= 0 && col < m->cols);
	m->data[row][col] = val;
}

Matrix * transpose(Matrix *m) {
	assert(m);
	Matrix *trans = make_matrix(m->cols, m->rows);
	for (int row = 0; row < m->rows; row++) {
		for (int col = 0; col < m->cols; col++) {
			matrix_set(trans, col, row, matrix_get(m, row, col));
		}
	}
	return trans;
}

Matrix * add_matrices(Matrix *a, Matrix *b) {
	assert(a);
	assert(b);
	assert(a->rows == b->rows && a->cols == b->cols);
	Matrix *m = make_matrix(a->rows, a->cols);
	for (int row = 0; row < a->rows; row++) {
		for (int col = 0; col < a->cols; col++) {
			matrix_set(m, row, col, matrix_get(a, row, col) + matrix_get(b, row, col));
		}
	}
	return m;
}

Matrix * multiply_matrices(Matrix *a, Matrix *b) {
	assert(a);
	assert(b);
	assert(a->cols == b->rows);
	Matrix *m = make_matrix(a->rows, b->cols);
	for (int i = 0; i < a->rows; i++) {
		for (int j = 0; j < b->cols; j++) {
			int sum = 0;
			for (int k = 0; k < a->cols; k++) {
				sum += matrix_get(a, i, k) * matrix_get(b, k, j);
			}
			matrix_set(m, i, j, sum);
		}
	}
	return m;
}

Matrix * hadamard_product(Matrix *a, Matrix *b) {
	assert(a);
	assert(b);
	assert(a->rows == b->rows && a->cols == b->cols);
	Matrix *m = make_matrix(a->rows, a->cols);
	for (int row = 0; row < a->rows; row++) {
		for (int col = 0; col < a->cols; col++) {
			matrix_set(m, row, col, matrix_get(a, row, col) * matrix_get(b, row, col));
		}
	}
	return m;
}
