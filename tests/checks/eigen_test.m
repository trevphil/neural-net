#include <stdlib.h>
#include <stdio.h>
#include "../../src/eigen.h"

static const double ERROR_TOLERANCE = 1e-4;

#suite Eigen

#test find_eigen_test
	int n = 3;
	Matrix *m = make_matrix(n, n);
	matrix_set(m, 0, 0, 1);
	matrix_set(m, 0, 1, 2);
	matrix_set(m, 0, 2, 5);
	matrix_set(m, 1, 0, 2);
	matrix_set(m, 1, 1, 3);
	matrix_set(m, 1, 2, 11);
	matrix_set(m, 2, 0, 5);
	matrix_set(m, 2, 1, 11);
	matrix_set(m, 2, 2, -20);

	double *eigenvalues = calloc(n, sizeof(double));
	Vector **eigenvectors = calloc(n, sizeof(Vector));
	find_eigen(m, eigenvalues, eigenvectors);
	
	ck_assert(fabs(eigenvalues[0] + 0.19128) <= ERROR_TOLERANCE);
	ck_assert(vector_length(eigenvectors[0]) == 3);
	ck_assert(fabs(vector_get(eigenvectors[0], 0) - 0.889148) <= ERROR_TOLERANCE);
	ck_assert(fabs(vector_get(eigenvectors[0], 1) + 0.456688) <= ERROR_TOLERANCE);
	ck_assert(fabs(vector_get(eigenvectors[0], 2) + 0.029170) <= ERROR_TOLERANCE);
	ck_assert(fabs(l2_norm(eigenvectors[0]) - 1.0) <= ERROR_TOLERANCE);
	free_vector(eigenvectors[0]);

	ck_assert(fabs(eigenvalues[1] - 9.19836) <= ERROR_TOLERANCE);
	ck_assert(vector_length(eigenvectors[1]) == 3);
	ck_assert(fabs(vector_get(eigenvectors[1], 0) - 0.432153) <= ERROR_TOLERANCE);
	ck_assert(fabs(vector_get(eigenvectors[1], 1) - 0.816994) <= ERROR_TOLERANCE);
	ck_assert(fabs(vector_get(eigenvectors[1], 2) - 0.381791) <= ERROR_TOLERANCE);
	ck_assert(fabs(l2_norm(eigenvectors[1]) - 1.0) <= ERROR_TOLERANCE);
	free_vector(eigenvectors[1]);

	ck_assert(fabs(eigenvalues[2] + 25.00707) <= ERROR_TOLERANCE);
	ck_assert(vector_length(eigenvectors[2]) == 3);
	ck_assert(fabs(vector_get(eigenvectors[2], 0) + 0.150527) <= ERROR_TOLERANCE);
	ck_assert(fabs(vector_get(eigenvectors[2], 1) + 0.352075) <= ERROR_TOLERANCE);
	ck_assert(fabs(vector_get(eigenvectors[2], 2) - 0.923788) <= ERROR_TOLERANCE);
	ck_assert(fabs(l2_norm(eigenvectors[2]) - 1.0) <= ERROR_TOLERANCE);
	free_vector(eigenvectors[2]);

	free_matrix(m);
	free(eigenvalues);
	free(eigenvectors);

#test sort_vectors_by_values_test1
	int n = 3;
	Matrix *m = make_matrix(n, n);
	matrix_set(m, 0, 0, 1);
	matrix_set(m, 0, 1, 2);
	matrix_set(m, 0, 2, 5);
	matrix_set(m, 1, 0, 2);
	matrix_set(m, 1, 1, 3);
	matrix_set(m, 1, 2, 11);
	matrix_set(m, 2, 0, 5);
	matrix_set(m, 2, 1, 11);
	matrix_set(m, 2, 2, -20);

	double *eigenvalues = calloc(n, sizeof(double));
	Vector **eigenvectors = calloc(n, sizeof(Vector));
	find_eigen(m, eigenvalues, eigenvectors);
	int descending = 1;
	sort_vectors_by_values(n, eigenvalues, eigenvectors, descending);

	ck_assert(fabs(eigenvalues[0] + 25.00707) <= ERROR_TOLERANCE);
	ck_assert(fabs(vector_get(eigenvectors[0], 0) + 0.150527) <= ERROR_TOLERANCE);
	ck_assert(fabs(vector_get(eigenvectors[0], 1) + 0.352075) <= ERROR_TOLERANCE);
	ck_assert(fabs(vector_get(eigenvectors[0], 2) - 0.923788) <= ERROR_TOLERANCE);
	free_vector(eigenvectors[0]);

	ck_assert(fabs(eigenvalues[1] - 9.19836) <= ERROR_TOLERANCE);
	ck_assert(fabs(vector_get(eigenvectors[1], 0) - 0.432153) <= ERROR_TOLERANCE);
	ck_assert(fabs(vector_get(eigenvectors[1], 1) - 0.816994) <= ERROR_TOLERANCE);
	ck_assert(fabs(vector_get(eigenvectors[1], 2) - 0.381791) <= ERROR_TOLERANCE);
	free_vector(eigenvectors[1]);
	
	ck_assert(fabs(eigenvalues[2] + 0.19128) <= ERROR_TOLERANCE);
	ck_assert(fabs(vector_get(eigenvectors[2], 0) - 0.889148) <= ERROR_TOLERANCE);
	ck_assert(fabs(vector_get(eigenvectors[2], 1) + 0.456688) <= ERROR_TOLERANCE);
	ck_assert(fabs(vector_get(eigenvectors[2], 2) + 0.029170) <= ERROR_TOLERANCE);
	free_vector(eigenvectors[2]);

	free_matrix(m);
	free(eigenvalues);
	free(eigenvectors);
	
#test sort_vectors_by_values_test2
	int n = 2;
	Matrix *m = make_matrix(n, n);
	matrix_set(m, 0, 0, 5);
	matrix_set(m, 0, 1, -2.5);
	matrix_set(m, 1, 0, -2.5);
	matrix_set(m, 1, 1, 12);

	double *eigenvalues = calloc(n, sizeof(double));
	Vector **eigenvectors = calloc(n, sizeof(Vector));
	find_eigen(m, eigenvalues, eigenvectors);
	int descending = 0;
	sort_vectors_by_values(n, eigenvalues, eigenvectors, descending);

	ck_assert(fabs(eigenvalues[0] - 4.19883) <= ERROR_TOLERANCE);
	ck_assert(fabs(vector_get(eigenvectors[0], 0) - 0.952296) <= ERROR_TOLERANCE);
	ck_assert(fabs(vector_get(eigenvectors[0], 1) - 0.305177) <= ERROR_TOLERANCE);
	free_vector(eigenvectors[0]);

	ck_assert(fabs(eigenvalues[1] - 12.80116) <= ERROR_TOLERANCE);
	ck_assert(fabs(vector_get(eigenvectors[1], 0) + 0.305177) <= ERROR_TOLERANCE);
	ck_assert(fabs(vector_get(eigenvectors[1], 1) - 0.952296) <= ERROR_TOLERANCE);
	free_vector(eigenvectors[1]);

	free_matrix(m);
	free(eigenvalues);
	free(eigenvectors);
