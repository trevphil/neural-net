#include "../../src/matrix.h"

#suite Matrix

#test make_matrix_test
	Matrix *m = make_matrix(5, 5);
	ck_assert(matrix_get(m, 0, 0) == 0);
	ck_assert(matrix_get(m, 4, 4) == 0);
	free_matrix(m);

#test matrix_get_set_test
	Matrix *m = make_matrix(5, 5);
	matrix_set(m, 1, 2, -12.5);
	matrix_set(m, 0, 3, 200.1);
	ck_assert(matrix_get(m, 1, 2) == -12.5);
	ck_assert(matrix_get(m, 0, 3) == 200.1);
	free_matrix(m);

#test identity_matrix_test
	Matrix *m = identity_matrix(5);
	ck_assert(rows(m) == 5 && cols(m) == 5);
	ck_assert(matrix_get(m, 0, 0) == 1);
	ck_assert(matrix_get(m, 2, 0) == 0);
	ck_assert(matrix_get(m, 4, 4) == 1);
	free_matrix(m);

#test copy_matrix_test
	Matrix *m = make_matrix(5, 5);
	matrix_set(m, 1, 2, -12.5);
	matrix_set(m, 0, 3, 200.1);
	Matrix *n = copy_matrix(m);
	ck_assert(matrix_get(n, 1, 2) == -12.5);
	ck_assert(matrix_get(n, 0, 3) == 200.1);
	free_matrix(m);
	free_matrix(n);
	
#test matrix_equality_test
	Matrix *a = make_matrix(5, 5);
	matrix_set(a, 1, 2, -12.5);
	matrix_set(a, 0, 3, 200.1);
	Matrix *b = copy_matrix(a);
	ck_assert(equal_matrices(a, b));
	matrix_set(a, 1, 3, 3.2);
	ck_assert(!equal_matrices(a, b));
	free_matrix(a);
	free_matrix(b);

#test rows_cols_matrix_test
	Matrix *m = make_matrix(21, 37);
	ck_assert(rows(m) == 21);
	ck_assert(cols(m) == 37);
	free_matrix(m);

#test transpose_matrix_test
	Matrix *m = make_matrix(20, 5);
	matrix_set(m, 0, 4, 123);
	matrix_set(m, 19, 3, 544);
	Matrix *n = transpose_matrix(m);
	ck_assert(rows(n) == 5 && cols(n) == 20);
	ck_assert(matrix_get(n, 4, 0) == 123);
	ck_assert(matrix_get(n, 3, 19) == 544);
	free_matrix(m);
	free_matrix(n);

#test add_matrices_test
	Matrix *a = make_matrix(2, 2);
	matrix_set(a, 0, 0, 5);
	matrix_set(a, 0, 1, 10);
	Matrix *b = make_matrix(2, 2);
	matrix_set(b, 0, 0, 5);
	matrix_set(b, 1, 0, 10);
	Matrix *c = add_matrices(a, b);
	ck_assert(matrix_get(c, 0, 0) == 10);
	ck_assert(matrix_get(c, 1, 0) == 10);
	ck_assert(matrix_get(c, 0, 1) == 10);
	free_matrix(a);
	free_matrix(b);
	free_matrix(c);
	
#test multiply_matrices_test
	Matrix *a = make_matrix(3, 2);
	matrix_set(a, 0, 0, 5);
	matrix_set(a, 2, 1, 10);
	Matrix *b = make_matrix(2, 5);
	matrix_set(b, 1, 4, 7);
	matrix_set(b, 1, 0, 10);
	Matrix *c = multiply_matrices(a, b);
	ck_assert(rows(c) == 3 && cols(c) == 5);
	ck_assert(matrix_get(c, 0, 0) == 0);
	ck_assert(matrix_get(c, 2, 0) == 100);
	ck_assert(matrix_get(c, 2, 4) == 70);
	free_matrix(a);
	free_matrix(b);
	free_matrix(c);
	
#test hadamard_product_test
	Matrix *a = make_matrix(2, 2);
	matrix_set(a, 0, 0, 5);
	matrix_set(a, 0, 1, 10);
	Matrix *b = make_matrix(2, 2);
	matrix_set(b, 0, 0, 5);
	matrix_set(b, 1, 0, 10);
	Matrix *c = hadamard_product(a, b);
	ck_assert(matrix_get(c, 0, 0) == 25);
	ck_assert(matrix_get(c, 1, 0) == 0);
	ck_assert(matrix_get(c, 0, 1) == 0);
	free_matrix(a);
	free_matrix(b);
	free_matrix(c);