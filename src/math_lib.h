#ifndef MATH_LIB_H
#define MATH_LIB_H

/*
 * Function:  sigmoid
 * --------------------
 * Computes the sigmoid function for input x.
 */
double sigmoid(double x);

/*
 * Function:  bounded_sigmoid
 * --------------------
 * Computes the sigmoid function for input x, but rather than bounded
 * by (0, 1) it is bounded by (minimum, maximum).
 */
double bounded_sigmoid(double x, double minimum, double maximum);

/*
 * Function:  normal_dist
 * --------------------
 * Computes g(x) where g is the normal distribution with the given
 * mean and variance in the parameters.
 */
double normal_dist(double x, double mean, double variance);

/*
 * Function:  std_normal_dist
 * --------------------
 * Computes g(x) where g is the standard normal distribution,
 * i.e. with mean=0 and variance=1.
 */
double std_normal_dist(double x);

#endif // MATH_LIB_H
