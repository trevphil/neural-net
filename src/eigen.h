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
 * have length N, given that the input is an NxN matrix.
 */
void find_eigen(Matrix *input, double *eigenvalues, Vector **eigenvectors);

#endif // EIGEN_H
