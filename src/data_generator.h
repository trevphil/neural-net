#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H

#include "vector.h"

/*
 * Function:  uniform_dist_sample
 * --------------------
 * Returns a random value from the uniform distribution
 * over [lower, upper].
 */
double uniform_dist_sample(double lower, double upper);

/*
 * Function:  normal_dist_sample
 * --------------------
 * Samples a random value from the normal distribution with the given
 * mean and variance.
 */
double normal_dist_sample(double mean, double variance);

/*
 * Function:  std_normal_dist_sample
 * --------------------
 * Samples a random value from the standard normal distribution,
 * i.e. with mean=0 and variance=1.
 */
double std_normal_dist_sample();

/*
 * Function:  generate_vectors
 * --------------------
 * Returns an array of 'n' number of vectors, each of which
 * has size/dimensionality 'd'. Each element in the vector is created by
 * applying the function 'f'. The random number generator is seeded at
 * the start of this function.
 */
Vector ** generate_vectors(int n, int d, double (*f)());

#endif // DATA_GENERATOR_H