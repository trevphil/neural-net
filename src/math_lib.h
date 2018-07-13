#ifndef MATH_LIB_H
#define MATH_LIB_H

/*
 * Function:  sigmoid 
 * --------------------
 * Computes the sigmoid function for input x
 */
double sigmoid(double x);

/*
 * Function:  boundedSigmoid 
 * --------------------
 * Computes the sigmoid function for input x, but rather than bounded
 * by (0, 1) it is bounded by (minimum, maximum)
 */
double boundedSigmoid(double x, double minimum, double maximum);

#endif // MATH_LIB_H