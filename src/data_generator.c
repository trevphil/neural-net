#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include "data_generator.h"

Vector ** generate_vectors(int n, int d, double (*f)(double), int lower, int upper) {
	assert(n >= 0 && d >= 0 && upper >= lower);
	assert(f);

	srand(time(NULL));
	double range = upper - lower;
	Vector ** generated = calloc(n, sizeof(Vector));
	for (int i = 0; i < n; i++) {
		Vector *v = make_vector(d);
		for (int j = 0; j < d; j++) {
			double randomVal = (double)rand() / RAND_MAX * range - upper;
			vector_set(v, j, f(randomVal));
		}
		generated[i] = v;
	}
	return generated;
}
