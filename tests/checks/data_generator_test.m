#include <stdlib.h>
#include <stdio.h>
#include "../../src/math_lib.h"
#include "../../src/data_generator.h"


#suite DataGenerator

#test generate_vectors_test
	Vector **generated = generate_vectors(10, 3, std_normal_dist, -2, 2);
	for (int i = 0; i < 10; i++) {
		Vector *v = generated[i];
		ck_assert(vector_length(v) == 3);
		ck_assert(vector_get(v, 0) <= 1.0);
		ck_assert(vector_get(v, 1) <= 1.0);
		ck_assert(vector_get(v, 2) <= 1.0);
		free_vector(v);
	}
	free(generated);
