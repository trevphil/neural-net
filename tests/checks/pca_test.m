#include <stdlib.h>
#include "../../src/pca.h"
#include "../../src/data_generator.h"

#suite PCA

#test pca_test
	// Principal Component Analysis (PCA) in action
	int vectorDimensions = 3;
	int reducedDimensions = 2;
	int sampleSize = 40;

	/*
	* The input is 40 vectors with 3 elements each. For 20 of them,
	* all values will come from the Standard Normal Distribution.
	* For the other 20 vectors, the LAST value will come from a 
	* Normal Distribution with mean 10 (rather than mean 0).
	*
	* The test will reduce the dimensionality from 3 to 2. If it works
	* correctly, it should "recognize" that the third element of the
	* vectors is an important distinguishing characteristic, and it should
	* map the 3D vectors into 2D vectors while preserving this
	* distinguishing trait.
	*
	* The result should be that TWO groupings emerge if you plot the
	* output vectors in 2D coordinate space. This can be checked programmatically
	* by finding the distance from the origin for each output vector, and
	* verifying that the distances fall into one of two categories - 
	* either close to or far from the origin.
	*/
	Vector **input = calloc(sampleSize, sizeof(Vector));
	for (int i = 0; i < sampleSize; i++) {
		Vector *v = make_vector(vectorDimensions);
		vector_set(v, 0, std_normal_dist_sample());
		vector_set(v, 1, std_normal_dist_sample());
		if (i < sampleSize / 2) {
			vector_set(v, 2, std_normal_dist_sample());
		} else {
			vector_set(v, 2, normal_dist_sample(10.0, 1.0));
		}
		input[i] = v;
	}

	Vector **output = pca(sampleSize, input, vectorDimensions, reducedDimensions);

	int grouping1Count = 0;
	int grouping2Count = 0;
	for (int i = 0; i < sampleSize; i++) {
		double distanceFromOrigin = l2_norm(output[i]);
		if (distanceFromOrigin < 5) {
			grouping1Count++;
		} else {
			grouping2Count++;
		}
	}

	ck_assert_msg(grouping1Count == 20 && grouping2Count == 20,
		"PCA did not preserve distinguishing data characteristics!");

	// Clean up.
	for (int i = 0; i < sampleSize; i++) {
		free_vector(input[i]);
		free_vector(output[i]);
	}
	free(input);
	free(output);
