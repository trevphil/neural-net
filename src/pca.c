#include <stdlib.h>
#include <assert.h>
#include "pca.h"
#include "matrix.h"
#include "eigen.h"

Vector ** pca(int sampleSize, Vector **input, int dimensionality, int reducedDimensionality) {
	assert(sampleSize > 0);
	assert(reducedDimensionality < dimensionality);
	assert(input);

	Vector **output = calloc(sampleSize, sizeof(Vector));
	
	// Combine the input vectors as columns of a matrix which has d=`dimensionality` rows.
	// Then compute a square scatter matrix which has shape d x d.
	Matrix *testData = vectors_to_matrix(sampleSize, input);
	Matrix *scatter = scatter_matrix(testData);
	assert(rows(scatter) == dimensionality && cols(scatter) == dimensionality);
	
	// Compute eigenvalues and eigenvectors of the scatter matrix, then sort them
	// from greatest to smallest in magnitude.
	double *eigenvalues = calloc(dimensionality, sizeof(double));
	Vector **eigenvectors = calloc(dimensionality, sizeof(Vector));
	find_eigen(scatter, eigenvalues, eigenvectors);
	int sortDescending = 1;
	sort_vectors_by_values(dimensionality, eigenvalues, eigenvectors, sortDescending);

	// Take only the k first sorted eigenvectors, where k=`reducedDimensionality`.
	Vector **temp = calloc(reducedDimensionality, sizeof(Vector));
	for (int i = 0; i < reducedDimensionality; i++) {
		temp[i] = copy_vector(eigenvectors[i]);
	}
	
	// Combine these eigenvectors into a matrix W and compute its transpose.
	Matrix *w = vectors_to_matrix(reducedDimensionality, temp);
	Matrix *transformer = transpose_matrix(w);
	
	// Now map input to output, i.e. for each input vector x,
	// construct output vector y from the equation y = (W^T) * x.
	for (int i = 0; i < sampleSize; i++) {
		Matrix *inputItem = vector_as_matrix(input[i]);
		Matrix *reduced = multiply_matrices(transformer, inputItem);
		assert(cols(reduced) > 0);
		output[i] = column_as_vector(reduced, 0);
		free_matrix(inputItem);
		free_matrix(reduced);
	}

	// Clean up.
	for (int i = 0; i < dimensionality; i++)
		free_vector(eigenvectors[i]);
	for (int i = 0; i < reducedDimensionality; i++)
		free_vector(temp[i]);
	free(eigenvalues);
	free(eigenvectors);
	free(temp);
	free_matrix(testData);
	free_matrix(scatter);
	free_matrix(w);
	free_matrix(transformer);

	return output;
}
