#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H

#include "vector.h"

/*
 * Function:  generate_vectors
 * --------------------
 * Returns an array of 'n' number of vectors, each of which
 * has size/dimensionality 'd'. Each element in the vector is created as follows:
 * a random number is taken from the range [lower, upper] and then the
 * function f is applied, so each vector value is f(random[lower, upper]).
 */
Vector ** generate_vectors(int n, int d, double (*f)(double), int lower, int upper);

#endif // DATA_GENERATOR_H