#ifndef EIGEN_H
#define EIGEN_H

#import "vector.h"
#import "matrix.h"

/*
 * Function:  find_eigen
 * --------------------
 * Computes the eigenvalues and eigenvectors of the REAL SYMMETRIC MATRIX
 * given as input. The results are written into the passed parameters,
 * so the array of eigenvalues and the array of eigenvectors should both
 * have length N, given that the input is an NxN matrix. The eigenvectors
 * will each have length of approximately 1.
 */
void find_eigen(Matrix *input, double *eigenvalues, Vector **eigenvectors);

/*
 * Function:  sort_vectors_by_values
 * --------------------
 * Will sort the given eigenvectors by their eigenvalues. For example,
 * given the eigenvalues [2, 3, 1] and their corresponding eigenvectors [X, Y, Z],
 * this function will reorder the two arrays to be [3, 2, 1] and [Y, X, Z]
 * if descending=1 (or the reverse if descending=0). The parameter `n` represents
 * the size of the arrays, which should be the SAME. They should be parallel arrays.
 * 
 * IMPORTANT NOTE: Sorting is done by the ABSOLUTE VALUE of the eigenvalues, not
 * based on their positive/negative sign.
 */
void sort_vectors_by_values(int n, double *eigenvalues, Vector **eigenvectors, int descending);

#endif // EIGEN_H
