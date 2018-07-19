#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "vector.h"

Vector * make_vector(int n) {
	assert(n >= 0);
	Vector *v = malloc(sizeof(Vector));
	v->length = n;
	v->matrix = make_matrix(n, 1);
	return v;
}


void free_vector(Vector *v) {
	if (v) {
		free_matrix(v->matrix);
		free(v);
		v = NULL;
	}
}

Vector * copy_vector(Vector *v) {
	if (!v) return NULL;
	Vector *x = make_vector(vector_length(v));
	free_matrix(x->matrix);
	x->matrix = copy_matrix(v->matrix);
	return x;
}

int equal_vectors(Vector *a, Vector *b) {
	if (!a) return 0;
	if (!b) return 0;
	if (vector_length(a) != vector_length(b)) return 0;
	return equal_matrices(a->matrix, b->matrix);
}

int vector_length(Vector *v) {
	assert(v);
	return v->length;
}

double vector_get(Vector *v, int i) {
	assert(v);
	assert(i >= 0 && i < vector_length(v));
	return matrix_get(v->matrix, i, 0);
}

void vector_set(Vector *v, int i, double val) {
	if (!v) return;
	assert(i >= 0 && i < vector_length(v));
	matrix_set(v->matrix, i, 0, val);
}

void print_vector(Vector *v) {
	if (!v) return;
	printf("<Vector: %p>; length=%d\n", v, vector_length(v));
	for (int i = 0; i < vector_length(v); i++) {
		printf("| %0.3f |\n", vector_get(v, i));
	}
}

Matrix * transpose_vector(Vector *v) {
	assert(v);
	return transpose_matrix(v->matrix);
}

Vector * add_vectors(Vector *x, Vector *y) {
	assert(x);
	assert(y);
	assert(vector_length(x) == vector_length(y));
	Vector *z = make_vector(vector_length(x));
	free_matrix(z->matrix);
	z->matrix = add_matrices(x->matrix, y->matrix);
	return z;
}

double dot_product(Vector *x, Vector *y) {
	assert(x);
	assert(y);
	int n = vector_length(x);
	assert(n > 0 && n == vector_length(y));
	double result = 0;
	for (int i = 0; i < n; i++) {
		result += vector_get(x, i) * vector_get(y, i);
	}
	return result;
}

double l1_norm(Vector *v) {
	return lp_norm(v, 1);
}

double l2_norm(Vector *v) {
	return lp_norm(v, 2);
}

double l2_sq_norm(Vector *v) {
	double norm = l2_norm(v);
	return norm * norm;
}

double lp_norm(Vector *v, double p) {
	assert(v);
	assert(vector_length(v) > 0);
	assert(p >= 0);
	double result = 0;
	for (int i = 0; i < vector_length(v); i++) {
		result += pow(fabs(vector_get(v, i)), p);
	}
	return pow(result, 1.0 / p);
}

double max_norm(Vector *v) {
	assert(v);
	int n = vector_length(v);
	assert(n > 0);
	double maxVal = fabs(vector_get(v, 0));
	for (int i = 1; i < n; i++) {
		double element = fabs(vector_get(v, i));
		maxVal = element > maxVal ? element : maxVal;
	}
	return maxVal;
}
