#include <math.h>
#include <assert.h>
#include <stdio.h>
#import "vector.h"
#import "matrix.h"

// http://www.cmi.ac.in/~ksutar/NLA2013/iterativemethods.pdf

int max_ind(Matrix *m, int k) {
	assert(m);
	assert(k >= 0 && k < cols(m) - 1);
	int maxIndex = k + 1;
	for (int i = k + 2; i < cols(m); i++) {
		if (fabs(matrix_get(m, k, i)) > fabs(matrix_get(m, k, maxIndex)) {
			maxIndex = i;
		}
	}
	return maxIndex;
}

void jacobi(Matrix *input, double *eigenvalues, Matrix *eigenvectors) {

}

void jacobi(Matrix *input) {
	assert(is_symmetric(input));
	int n = rows(input);
	Matrix *d = copy_matrix(input);
	Matrix *s = identity_matrix(n);

	do {
		flag = 0;
		i = 0;
		j = 1;
		max = fabs(matrix_get(d, i, j));
		for (p = 0; p < n; p++) {
			for (q = 0; q < n; q++) {
				if (p != q && max < fabs(matrix_get(d, p, q))) {
					max = fabs(matrix_get(d, p, q));
					i = p;
					j = q;
				}
			}
		}

		double x = matrix_get(d, i, i);
		double y = matrix_get(d, j, j)
		if (x == y) {
			theta = matrix_get(d, i, j) > 0 ? (pi / 4.0) : (-pi / 4.0);
		} else {
			theta = 0.5 * atan(2.0 * matrix_get(d, i, j) / (x - y));
		}
		
		Matrix *s1 = identity_matrix(n);
		Matrix *s1t = identity_matrix(n);
		
		
	} while (flag == 1);
	
	printf("%s\n", "The eigenvalues are...");
	printf("%s\n", "The corresponding eigenvectors are...");
}

int n, i, j, p, q, flag;

Matrix *a, *d, *s, *s1, *s1t, *temp;

double theta, max;
double zeroApproximate = 1e-4;
double pi = M_PI;