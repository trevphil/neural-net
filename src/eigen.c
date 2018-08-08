#include <math.h>
#include <assert.h>
#include "eigen.h"

// Algorithms adapted from this source:
// http://www.cmi.ac.in/~ksutar/NLA2013/iterativemethods.pdf

void jacobi(Matrix *input, double *eigenvalues, Vector **eigenvectors) {
	assert(is_symmetric(input) && rows(input) > 1);
	int n = rows(input);
	double zeroApproximate = 1e-4;
	double pi = M_PI;
	double theta;
	Matrix *d = copy_matrix(input);
	Matrix *s = identity_matrix(n);
	int flag, p, q;

	do {
		flag = 0;
		int i = 0;
		int j = 1;
		double max = fabs(matrix_get(d, i, j));
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
		double y = matrix_get(d, j, j);
		if (x == y) {
			theta = matrix_get(d, i, j) > 0 ? (pi / 4.0) : (-pi / 4.0);
		} else {
			theta = 0.5 * atan(2.0 * matrix_get(d, i, j) / (x - y));
		}
		double cosTheta = cos(theta);
		double sinTheta = sin(theta);

		Matrix *s1 = identity_matrix(n);
		matrix_set(s1, i, i, cosTheta);
		matrix_set(s1, j, j, cosTheta);
		matrix_set(s1, j, i, sinTheta);
		matrix_set(s1, i, j, -sinTheta);

		Matrix *s1t = identity_matrix(n);
		matrix_set(s1t, i, i, cosTheta);
		matrix_set(s1t, j, j, cosTheta);
		matrix_set(s1t, j, i, -sinTheta);
		matrix_set(s1t, i, j, sinTheta);

		Matrix *temp = make_matrix(n, n);
		for (int row = 0; row < n; row++) {
			for (int col = 0; col < n; col++) {
				for (p = 0; p < n; p++) {
					double currentVal = matrix_get(temp, row, col);
					double product = matrix_get(s1t, row, p) * matrix_get(d, p, col);
					matrix_set(temp, row, col, currentVal + product);
				}
			}
		}

		for (int row = 0; row < n; row++) {
			for (int col = 0; col < n; col++) {
				matrix_set(d, row, col, 0);
				for (p = 0; p < n; p++) {
					double currentVal = matrix_get(d, row, col);
					double product = matrix_get(temp, row, p) * matrix_get(s1, p, col);
					matrix_set(d, row, col, currentVal + product);
				}
			}
		}

		for (int row = 0; row < n; row++) {
			for (int col = 0; col < n; col++) {
				matrix_set(temp, row, col, 0);
				for (p = 0; p < n; p++) {
					double currentVal = matrix_get(temp, row, col);
					double product = matrix_get(s, row, p) * matrix_get(s1, p, col);
					matrix_set(temp, row, col, currentVal + product);
				}
			}
		}

		free_matrix(s);
		s = copy_matrix(temp);

		for (int row = 0; row < n; row++) {
			for (int col = 0; col < n; col++) {
				if (row != col && fabs(matrix_get(d, row, col)) > zeroApproximate) {
					flag = 1;
					break;
				}
			}
			if (flag) break;
		}
		
		free_matrix(s1);
		free_matrix(s1t);
		free_matrix(temp);
	} while (flag);

	// Extract eigenvalues and eigenvectors, write them into the passed arguments
	for (int i = 0; i < n; i++) {
		eigenvalues[i] = matrix_get(d, i, i);
		eigenvectors[i] = column_as_vector(s, i);
	}

	free_matrix(d);
	free_matrix(s);
}

void find_eigen(Matrix *input, double *eigenvalues, Vector **eigenvectors) {
	// The Jacobi iterative algorithm will be used for now, until
	// I have the desire/need to optimize further.
	jacobi(input, eigenvalues, eigenvectors);
}

int partition_parallel(double *arr1, Vector **arr2, int low, int high, int descending) {
    double pivot = fabs(arr1[high]);
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
		int swapNeeded = descending ? fabs(arr1[j]) >= pivot : fabs(arr1[j]) <= pivot;
        if (swapNeeded) {
            i++;
			// Perform swap for array 1
			double tmp1 = arr1[i];
			arr1[i] = arr1[j];
			arr1[j] = tmp1;
			// Perform swap for array 2
			Vector *tmp2 = arr2[i];
			arr2[i] = arr2[j];
			arr2[j] = tmp2;
        }
    }

	// Perform swap for array 1
	double tmp1 = arr1[i + 1];
	arr1[i + 1] = arr1[high];
	arr1[high] = tmp1;
	// Perform swap for array 2
	Vector *tmp2 = arr2[i + 1];
	arr2[i + 1] = arr2[high];
	arr2[high] = tmp2;

    return i + 1;
}

void quick_sort_parallel(double *arr1, Vector **arr2, int low, int high, int descending) {
    if (low < high) {
        int partitionIndex = partition_parallel(arr1, arr2, low, high, descending);
        quick_sort_parallel(arr1, arr2, low, partitionIndex - 1, descending);
        quick_sort_parallel(arr1, arr2, partitionIndex + 1, high, descending);
    }
}

void sort_vectors_by_values(int n, double *eigenvalues, Vector **eigenvectors, int descending) {
	// Use a slightly modified version of quicksort to perform this operation
	quick_sort_parallel(eigenvalues, eigenvectors, 0, n - 1, descending);
}
