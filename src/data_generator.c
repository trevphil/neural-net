#include <assert.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "data_generator.h"

double uniform_dist_sample(double lower, double upper) {
	assert(upper >= lower);
	double range = upper - lower;
	return (double)rand() / (double)RAND_MAX * range + lower;
}

double normal_dist_sample(double mean, double variance) {
	assert(variance >= 0);
	
	double stdDev = sqrt(variance);
	double x = uniform_dist_sample(0, 1);
	double y = uniform_dist_sample(0, 1);
	double intermediary1 = sqrt(-2.0 * log(x));
	double intermediary2 = cos(2 * M_PI * y);
	double stdNormal = intermediary1 * intermediary2;
	return stdNormal * stdDev + mean;
}

double std_normal_dist_sample() {
	return normal_dist_sample(0.0, 1.0);
}

Vector ** generate_vectors(int n, int d, double (*f)()) {
	assert(n >= 0 && d >= 0);
	assert(f);

	srand(time(NULL));
	Vector ** generated = calloc(n, sizeof(Vector));
	for (int i = 0; i < n; i++) {
		Vector *v = make_vector(d);
		for (int j = 0; j < d; j++) {
			vector_set(v, j, f());
		}
		generated[i] = v;
	}
	return generated;
}

