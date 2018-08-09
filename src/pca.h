#ifndef PCA_H
#define PCA_H

#import "vector.h"

/*
 * Function:  pca
 * --------------------
 * Perform Principal Component Analysis (PCA) on the given input vectors.
 * Parameters are `input` which is an array of `sampleSize` number of vectors.
 * Each input vector should have `dimensionality` number of elements. The return value is
 * an array of `sampleSize` output vectors, each of which has `reducedDimensionality` number
 * of elements. The input vectors are not freed. The output vectors are allocated on the heap.
 */
Vector ** pca(int sampleSize, Vector **input, int dimensionality, int reducedDimensionality);

#endif // PCA_H
