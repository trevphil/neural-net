#include <math.h>
#include "../../src/matrix.h"
#include "../../src/vector.h"

static const double ERROR_TOLERANCE = 1e-9;

#suite Vector

#test make_vector_test
	Vector *v = make_vector(10);
	ck_assert(v);
	ck_assert(vector_length(v) == 10);
	ck_assert(vector_get(v, 0) == 0);
	ck_assert(vector_get(v, 9) == 0);
	free_vector(v);

#test vector_get_set_test
	Vector *v = make_vector(10);
	vector_set(v, 0, 22.78);
	vector_set(v, 9, -100.2);
	ck_assert(vector_get(v, 0) == 22.78);
	ck_assert(vector_get(v, 9) == -100.2);
	free_vector(v);

#test copy_vector_test
	Vector *x = make_vector(10);
	vector_set(x, 0, 22.78);
	vector_set(x, 9, -100.2);
	Vector *y = copy_vector(x);
	ck_assert(y);
	ck_assert(vector_length(y) == 10);
	ck_assert(vector_get(y, 0) == 22.78);
	ck_assert(vector_get(y, 9) == -100.2);
	free_vector(x);
	free_vector(y);
	
#test vector_as_matrix_test
	Vector *v = make_vector(5);
	vector_set(v, 0, 3);
	vector_set(v, 2, 11.5);
	Matrix *m = vector_as_matrix(v);
	ck_assert(rows(m) == 5);
	ck_assert(cols(m) == 1);
	ck_assert(matrix_get(m, 0, 0) == 3);
	ck_assert(matrix_get(m, 1, 0) == 0);
	ck_assert(matrix_get(m, 2, 0) == 11.5);
	free_vector(v);
	free_matrix(m);

#test vector_equality_test
	Vector *a = make_vector(5);
	vector_set(a, 1, 2);
	vector_set(a, 3, 1.2);
	Vector *b = copy_vector(a);
	ck_assert(equal_vectors(a, b));
	vector_set(a, 0, 3.2);
	ck_assert(!equal_vectors(a, b));
	free_vector(a);
	free_vector(b);

#test vector_length_test
	Vector *v = make_vector(200);
	ck_assert(vector_length(v) == 200);
	free_vector(v);

#test transpose_vector_test
	Vector *v = make_vector(5);
	for (int i = 0; i < vector_length(v); i++) {
		vector_set(v, i, i);
	}
	Matrix *m = transpose_vector(v);
	ck_assert(rows(m) == 1 && cols(m) == vector_length(v));
	for (int i = 0; i < cols(m); i++) {
		ck_assert(matrix_get(m, 0, i) == i);
	}
	free_vector(v);
	free_matrix(m);

#test add_vectors_test
	int n = 5;
	Vector *x = make_vector(n);
	Vector *y = make_vector(n);
	for (int i = 0; i < n; i++) {
		vector_set(x, i, i);
		vector_set(y, i, n - i);
	}
	Vector *z = add_vectors(x, y);
	ck_assert(z && vector_length(z) == n);
	for (int i = 0; i < n; i++) ck_assert(vector_get(z, i) == n);
	free_vector(x);
	free_vector(y);
	free_vector(z);
	
#test scale_vector_test
	Vector *v = make_vector(3);
	vector_set(v, 0, 0.5);
	vector_set(v, 1, 1);
	vector_set(v, 2, -20);
	scale_vector(v, 2);
	ck_assert(vector_get(v, 0) == 1);
	ck_assert(vector_get(v, 1) == 2);
	ck_assert(vector_get(v, 2) == -40);
	free_vector(v);

#test dot_product_test
	int n = 3;
	Vector *x = make_vector(n);
	Vector *y = make_vector(n);
	double expected = 0;
	for (int i = 0; i < n; i++) {
		vector_set(x, i, i);
		vector_set(y, i, i + 2);
		expected += i * (i + 2);
	}
	ck_assert(dot_product(x, y) == expected);
	free_vector(x);
	free_vector(y);

#test l1_norm_test
	int n = 10;
	Vector *v = make_vector(n);
	double expected = 0;
	for (int i = 0; i < n; i++) {
		vector_set(v, i, i * 2.0);
		expected += fabs(i * 2.0);
	}
	ck_assert(l1_norm(v) == expected);
	free_vector(v);

#test l2_norm_test
	int n = 3;
	Vector *v = make_vector(n);
	vector_set(v, 0, 12);
	vector_set(v, 1, 0.5);
	vector_set(v, 2, -8);
	double expected = 14.4308696897;
	ck_assert(fabs(l2_norm(v) - expected) <= ERROR_TOLERANCE);
	free_vector(v);

#test l2_sq_norm_test
	int n = 3;
	Vector *v = make_vector(n);
	vector_set(v, 0, 12);
	vector_set(v, 1, 0.5);
	vector_set(v, 2, -5);
	double expected = 169.25;
	ck_assert(fabs(l2_sq_norm(v) - expected) <= ERROR_TOLERANCE);
	free_vector(v);

#test lp_norm_test
	int n = 3;
	Vector *v = make_vector(n);
	vector_set(v, 0, 3.3);
	vector_set(v, 1, -0.75);
	vector_set(v, 2, -8);
	double expected = 8.18505544408;
	ck_assert(fabs(lp_norm(v, 3) - expected) <= ERROR_TOLERANCE);
	free_vector(v);

#test max_norm_test
	int n = 3;
	Vector *v = make_vector(n);
	vector_set(v, 0, -5);
	vector_set(v, 1, 4);
	vector_set(v, 2, -5.00001);
	double expected = 5.00001;
	ck_assert(fabs(max_norm(v) - expected) <= ERROR_TOLERANCE);
	vector_set(v, 0, -100);
	expected = 100;
	ck_assert(fabs(max_norm(v) - expected) <= ERROR_TOLERANCE);
	free_vector(v);
	
#test mean_vector_test
	Matrix *m = make_matrix(3, 3);
	matrix_set(m, 0, 0, 1);
	matrix_set(m, 0, 1, 2);
	matrix_set(m, 0, 2, 3);
	matrix_set(m, 2, 0, 2);
	matrix_set(m, 2, 1, 2);
	matrix_set(m, 2, 2, 2);
	Vector *meanV = mean_vector(m);
	ck_assert_msg(vector_get(meanV, 0) == 2, "vector[0] should be 2");
	ck_assert_msg(vector_get(meanV, 1) == 0, "vector[1] should be 0");
	ck_assert_msg(vector_get(meanV, 2) == 2, "vector[2] should be 2");
	free_matrix(m);
	free_vector(meanV);
