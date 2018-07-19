#ifndef MATRIX_H
#define MATRIX_H

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
 * Function:  identity_matrix
 * --------------------
 * Returns a new nxn Identity matrix, allocated on the heap.
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

#endif // MATRIX_H