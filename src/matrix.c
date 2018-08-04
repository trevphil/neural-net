#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "matrix.h"
#include "vector.h"

Matrix * make_matrix(int n_rows, int n_cols) {
	assert(n_rows >= 0 && n_cols >= 0);
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
	Matrix *x = make_matrix(rows(m), cols(m));
	for (int row = 0; row < rows(m); row++) {
		for (int col = 0; col < cols(m); col++) {
			matrix_set(x, row, col, matrix_get(m, row, col));
		}
	}
	return x;
}

int equal_matrices(Matrix *a, Matrix *b) {
	if (!a) return 0;
	if (!b) return 0;
	if (rows(a) != rows(b) || cols(a) != cols(b)) return 0;
	for (int row = 0; row < rows(a); row++) {
		for (int col = 0; col < cols(b); col++) {
			if (matrix_get(a, row, col) != matrix_get(b, row, col)) return 0;
		}
	}
	return 1;
}

int rows(Matrix *m) {
	assert(m);
	return m->rows;
}

int cols(Matrix *m) {
	assert(m);
	return m->cols;
}

double matrix_get(Matrix *m, int row, int col) {
	assert(m);
	assert(row >= 0 && row < rows(m));
	assert(col >= 0 && col < cols(m));
	return m->data[row][col];
}

void matrix_set(Matrix *m, int row, int col, double val) {
	if (!m) return;
	assert(row >= 0 && row < rows(m));
	assert(col >= 0 && col < cols(m));
	m->data[row][col] = val;
}

void print_matrix(Matrix *m) {
	if (!m) return;
	printf("<Matrix: %p>; size=%dx%d\n", m, rows(m), cols(m));
	for (int row = 0; row < rows(m); row++) {
		printf("%s", "| ");
		for (int col = 0; col < cols(m); col++) {
			double val = matrix_get(m, row, col);
			printf("%0.3f\t", val);
		}
		printf("%s\n", "|");
	}
}

Matrix * identity_matrix(int n) {
	assert(n >= 0);
	Matrix *m = make_matrix(n, n);
	for (int i = 0; i < n; i++) {
		matrix_set(m, i, i, 1);
	}
	return m;
}

Matrix * transpose_matrix(Matrix *m) {
	assert(m);
	Matrix *trans = make_matrix(cols(m), rows(m));
	for (int row = 0; row < rows(m); row++) {
		for (int col = 0; col < cols(m); col++) {
			matrix_set(trans, col, row, matrix_get(m, row, col));
		}
	}
	return trans;
}

Matrix * add_matrices(Matrix *a, Matrix *b) {
	assert(a);
	assert(b);
	assert(rows(a) == rows(b) && cols(a) == cols(b));
	Matrix *m = make_matrix(rows(a), cols(a));
	for (int row = 0; row < rows(a); row++) {
		for (int col = 0; col < cols(a); col++) {
			matrix_set(m, row, col, matrix_get(a, row, col) + matrix_get(b, row, col));
		}
	}
	return m;
}

Matrix * multiply_matrices(Matrix *a, Matrix *b) {
	assert(a);
	assert(b);
	assert(cols(a) == rows(b));
	Matrix *m = make_matrix(rows(a), cols(b));
	for (int i = 0; i < rows(a); i++) {
		for (int j = 0; j < cols(b); j++) {
			int sum = 0;
			for (int k = 0; k < cols(a); k++) {
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
	assert(rows(a) == rows(b) && cols(a) == cols(b));
	Matrix *m = make_matrix(rows(a), cols(a));
	for (int row = 0; row < rows(a); row++) {
		for (int col = 0; col < cols(a); col++) {
			matrix_set(m, row, col, matrix_get(a, row, col) * matrix_get(b, row, col));
		}
	}
	return m;
}

Matrix * scatter_matrix(Matrix *m) {
	// FIXME - Avoid memory leaks!!!
	// 3(a) - https://sebastianraschka.com/Articles/2014_pca_step_by_step.html
	assert(m);
	assert(rows(m) > 0 && cols(m) > 0);
	Vector *meanV = mean_vector(m);
	Matrix *scatter = make_matrix(rows(m), rows(m));
	scale_vector(meanV, -1);
	for (int k = 0; k < cols(m); k++) {
		// Vector *v = add_vectors()
		//Matrix *z = 
	}
	return NULL;
}