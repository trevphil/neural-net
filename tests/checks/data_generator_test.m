#include <stdlib.h>
#include <time.h>
#include "../../src/math_lib.h"
#include "../../src/data_generator.h"


#suite DataGenerator

#test uniform_dist_sample_test
	srand(time(NULL));
	for (int i = 0; i < 1000; i += 10) {
		double result = uniform_dist_sample(0, i);
		ck_assert(result >= 0 && result <= i);
	}
	
#test normal_dist_sample_test
	srand(time(NULL));
	int count = 0;
	int sampleSize = 1000;
	for (int i = 0; i < sampleSize; i++) {
		double x = normal_dist_sample(2, 16);
		if (x < -4 || x > 8) count++;
	}
	int expected = (int)(sampleSize * 0.1336);
	int marginOfError = (int)(expected * 0.1);
	ck_assert_msg(count <= expected + marginOfError,
		"Normal distribution produced an unexpectedly high number of tail-ended values!");
		
#test std_normal_dist_sample_test
	srand(time(NULL));
	int count = 0;
	int sampleSize = 1000;
	for (int i = 0; i < sampleSize; i++) {
		double x = std_normal_dist_sample();
		if (x < -2 || x > 2) count++;
	}
	int expected = (int)(sampleSize * 0.0455);
	int marginOfError = (int)(expected * 0.1);
	ck_assert_msg(count <= expected + marginOfError,
		"Std normal distribution produced an unexpectedly high number of tail-ended values!");

#test generate_vectors_test
	int vectorSize = 3;
	Vector **generated = generate_vectors(10, vectorSize, std_normal_dist_sample);
	for (int i = 0; i < 10; i++) {
		Vector *v = generated[i];
		// All values ought to be within 4 std. deviations i.e. [-4, 4]
		ck_assert(vector_length(v) == vectorSize);
		ck_assert(vector_get(v, 0) >= -4 && vector_get(v, 0) <= 4);
		ck_assert(vector_get(v, 1) >= -4 && vector_get(v, 1) <= 4);
		ck_assert(vector_get(v, 2) >= -4 && vector_get(v, 2) <= 4);
		free_vector(v);
	}
	free(generated);
