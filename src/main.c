#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matrix.h"
#include "vector.h"
#include "data_generator.h"
#include "eigen.h"

double normal_mean0() {
	return normal_dist_sample(0.0, 1.0);
}

double normal_mean10() {
	return normal_dist_sample(10.0, 1.0);
}

int main(int argc, char **argv) {
	// Principal Component Analysis (PCA) in action
	int vectorDimensions = 3;
	int reducedDimensions = 2;
	int sampleSize = 40;

	Vector **generated1 = generate_vectors(sampleSize/2, vectorDimensions, normal_mean0);
	Vector **generated2 = generate_vectors(sampleSize/2, vectorDimensions, normal_mean10);
	Vector **generated = calloc(sampleSize, sizeof(Vector));
	Vector **output = calloc(sampleSize, sizeof(Vector));

	for (int i = 0; i < sampleSize/2; i++) {
		generated[i] = generated1[i];
		generated[i + sampleSize/2] = generated2[i];
	}

	Matrix *testData = vectors_to_matrix(sampleSize, generated, 0);
	Matrix *scatter = scatter_matrix(testData);
	assert(rows(scatter) == vectorDimensions && cols(scatter) == vectorDimensions);
	
	double *eigenvalues = calloc(vectorDimensions, sizeof(double));
	Vector **eigenvectors = calloc(vectorDimensions, sizeof(Vector));
	find_eigen(scatter, eigenvalues, eigenvectors);
	int sortDescending = 1;
	sort_vectors_by_values(vectorDimensions, eigenvalues, eigenvectors, sortDescending);

	Vector **temp = calloc(reducedDimensions, sizeof(Vector));
	for (int i = 0; i < reducedDimensions; i++) {
		temp[i] = eigenvectors[i];
	}
	Matrix *w = vectors_to_matrix(reducedDimensions, temp, 1);
	Matrix *transformer = transpose_matrix(w);
	
	for (int i = 0; i < sampleSize; i++) {
		Matrix *inputItem = vector_as_matrix(generated[i]);
		Matrix *reduced = multiply_matrices(transformer, inputItem);
		assert(cols(reduced) > 0);
		output[i] = column_as_vector(reduced, 0);
		free_matrix(inputItem);
		free_matrix(reduced);
	}
	
	for (int i = 0; i < vectorDimensions; i++)
		free_vector(eigenvectors[i]);
	free(eigenvectors);
	free(generated1);
	free(generated2);
	free(eigenvalues);
	free(temp);
	free_matrix(testData);
	free_matrix(scatter);
	free_matrix(w);
	free_matrix(transformer);
	for (int i = 0; i < sampleSize; i++) {
		print_vector(output[i]);
	}
	// don't free `generated`, assume it is the "input" to the function
	// return output;
	
	return 0;
}
