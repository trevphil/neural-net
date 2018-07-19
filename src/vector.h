#ifndef VECTOR_H
#define VECTOR_H

#include "matrix.h"

/*
 * Data-structure:  Vector
 * --------------------
 * A vector of doubles. Internally implemented as a
 * matrix with column size of 1.
 */
struct Vector {
	int length;
	Matrix *matrix;
} typedef Vector;

/*
 * Function:  make_vector
 * --------------------
 * Returns a pointer to a Vector with size n.
 * All values are initialized to zero.
 * The vector is allocated on the heap.
 */
Vector * make_vector(int n);

/*
 * Function:  free_vector
 * --------------------
 * Deallocates the given vector in memory.
 */
void free_vector(Vector *v);

/*
 * Function:  copy_vector
 * --------------------
 * Returns a new vector with identical size to the given vector
 * and containing identical values. The new vector is allocated
 * to a different location in the heap than the given vector.
 */
Vector * copy_vector(Vector *v);

/*
 * Function:  vector_length
 * --------------------
 * Returns the size of the given vector v.
 */
int vector_length(Vector *v);

/*
 * Function:  vector_get
 * --------------------
 * Returns the value at position i in the vector (zero-indexed).
 */
double vector_get(Vector *v, int i);

/*
 * Function:  vector_set
 * --------------------
 * Set the value at position i within the given vector to the
 * value 'val'. The position is zero-indexed.
 */
void vector_set(Vector *v, int i, double val);

/*
 * Function:  transpose_vector
 * --------------------
 * Returns the transpose of the given vector v, i.e. a matrix
 * with 1 row and n columns (where n is the size of vector v).
 * The new matrix is allocated on the heap.
 */
Matrix * transpose_vector(Vector *v);

/*
 * Function:  add_vectors
 * --------------------
 * Returns a new vector which is the result of performing vector
 * addition on the two vectors x and y. The new vector is allocated
 * on the heap.
 */
Vector * add_vectors(Vector *x, Vector *y);

/*
 * Function:  dot_product
 * --------------------
 * Computes the dot-product of the two given vectors x and y.
 */
double dot_product(Vector *x, Vector *y);

/*
 * Function:  l1_norm
 * --------------------
 * Computes the L1 norm of the given vector v. In other words,
 * summing the absolute value of all items in v.
 */
double l1_norm(Vector *v);

/*
 * Function:  l2_norm
 * --------------------
 * Computes the L2 norm of the given vector v. In other words,
 * the Euclidean distance from the origin to the point identiﬁed by v.
 */
double l2_norm(Vector *v);

/*
 * Function:  l2_sq_norm
 * --------------------
 * Computes the L2 squared norm of the given vector v. It is simply
 * a convenience function for computing l2_norm(v) * l2_norm(v).
 */
double l2_sq_norm(Vector *v);

/*
 * Function:  lp_norm
 * --------------------
 * Computes the Lp norm of the given vector v.
 */
double lp_norm(Vector *v, double p);

/*
 * Function:  max_norm
 * --------------------
 * Computes the max norm of the given vector v. In other words,
 * the absolute value of the element with the largest magnitude in v.
 */
double max_norm(Vector *v);

#endif // VECTOR_H
