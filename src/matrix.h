#ifndef MATRIX_H
#define MATRIX_H

/* Vector imports Matrix, this avoids the dependency loop */
typedef struct Vector Vector;

/*
 * Data-structure:  Matrix
 * --------------------
 * A 2D matrix of double values
 */
struct Matrix {
	int rows;
	int cols;
	double **data;
} typedef Matrix;

/*
 * Function:  make_matrix
 * --------------------
 * Returns a pointer to a Matrix with n_rows number of rows and
 * n_cols number of columns. All values are initialized to zero.
 * The matrix is allocated on the heap.
 */
Matrix * make_matrix(int n_rows, int n_cols);

/*
 * Function:  free_matrix
 * --------------------
 * Deallocates the given matrix in memory.
 */
void free_matrix(Matrix *m);

/*
 * Function:  copy_matrix
 * --------------------
 * Returns a new matrix with identical size to the given matrix
 * and containing identical values. The new matrix is allocated
 * to a different location in the heap than the given matrix.
 */
Matrix * copy_matrix(Matrix *m);

/*
 * Function:  equal_matricies
 * --------------------
 * Returns 1 if the matrices are equal (and both non-null),
 * and 0 otherwise.
 */
int equal_matrices(Matrix *a, Matrix *b);

/*
 * Function:  rows
 * --------------------
 * Given a matrix M, returns the number of rows in M.
 */
int rows(Matrix *m);

/*
 * Function:  cols
 * --------------------
 * Given a matrix M, returns the number of columns in M.
 */
int cols(Matrix *m);

/*
 * Function:  matrix_get
 * --------------------
 * Given a matrix M, returns the double value located at
 * position (row, col) in M.
 */
double matrix_get(Matrix *m, int row, int col);

/*
 * Function:  matrix_set
 * --------------------
 * Given a matrix M, sets the double value located at
 * position (row, col) in M to the value 'val'.
 */
void matrix_set(Matrix *m, int row, int col, double val);

/*
 * Function:  column_as_vector
 * --------------------
 * Given a matrix M and zero-indexed column 'col', returns
 * the values in that column as a matrix
 */
Vector * column_as_vector(Matrix *m, int col);

/*
 * Function:  vectors_to_matrix
 * --------------------
 * Given an array of N vectors which MUST be the same size M,
 * will "merge" them into a matrix with shape M x N.
 * The given vectors will be FREED from memory if discardable != 0.
 */
Matrix * vectors_to_matrix(int numVectors, Vector **vectors, int discardable);

/*
 * Function:  print_matrix
 * --------------------
 * Prints an easy-to-read representation of M to stdout.
 */
void print_matrix(Matrix *m);

/*
 * Function:  identity_matrix
 * --------------------
 * Returns a new nxn Identity matrix, allocated on the heap.
 * A square matrix with 1's on the diagonal, 0's everywhere else.
 */
Matrix * identity_matrix(int n);

/*
 * Function:  transpose
 * --------------------
 * Returns a new matrix which is the transpose of the given matrix M.
 */
Matrix * transpose_matrix(Matrix *m);

/*
 * Function:  add_matrices
 * --------------------
 * Returns a new matrix which is the result of performing matrix
 * addition on the two matrices A and B. The new matrix is allocated
 * on the heap.
 */
Matrix * add_matrices(Matrix *a, Matrix *b);

/*
 * Function:  add_matrices_inplace
 * --------------------
 * Adds values from matrix B to the corresponding elements in A.
 * This mutates A and returns nothing.
 */
void add_matrices_inplace(Matrix *a, Matrix *b);

/*
 * Function:  multiply_matrices
 * --------------------
 * Returns a new matrix which is the result of performing matrix
 * multiplication on the two matrices A and B. The new matrix is allocated
 * on the heap.
 */
Matrix * multiply_matrices(Matrix *a, Matrix *b);

/*
 * Function:  hadamard_product
 * --------------------
 * Returns a new matrix which is the result of performing Hadamard
 * multiplication on the two matrices A and B, i.e. pairwise multiplication
 * for elements in the same position.
 */
Matrix * hadamard_product(Matrix *a, Matrix *b);

/*
 * Function:  is_symmetric
 * --------------------
 * Returns a non-zero value if the matrix M is symmetric, i.e. if it is
 * equal to its transpose. Consequently it must be a square matrix.
 */
int is_symmetric(Matrix *m);

/*
 * Function:  scatter_matrix
 * --------------------
 * Let's say each column of M is a vector x of length m. Let's say there are
 * n columns in matrix M. Let meanV be the mean vector for M, i.e. each value
 * in meanV is the average value for that row in M. Now for each column vector
 * v in M, we compute Z = (v - meanV) * transpose(v - meanV). The sum of all
 * of these Z matrices from 1 to n is the scatter matrix. Its size is m x m.
 */
Matrix * scatter_matrix(Matrix *m);

#endif // MATRIX_H