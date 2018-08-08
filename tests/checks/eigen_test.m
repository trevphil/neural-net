#include <stdlib.h>
#include <stdio.h>
#include "../../src/eigen.h"

// static const double ERROR_TOLERANCE = 1e-10;

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
	double eigenvalues[n]; // expected -0.19128, 9.19836, -25.00707
	Vector *eigenvectors[n]; // expected...
	// < -30.48116,	15.65586,	1 >
	// < 1.13191,	2.13989,	1 >
	// < -0.16295,	-0.38112,	1 >
	find_eigen(m, &eigenvalues, &eigenvectors);
	for (int i = 0; i < n; i++) {
		printf("Eigenvalue %d is %f\n", i, eigenvalues[i]);
		printf("%s\n", "The corresponding eigenvector is");
		print_vector(eigenvectors[i]);
		printf("%s\n", "");
		free_vector(eigenvectors[i]);
	}
	free_matrix(m);