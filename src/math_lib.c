#include <math.h>
#include <assert.h>
#include "math_lib.h"

static const double e = M_E;
static const double pi = M_PI;

double bounded_sigmoid(double x, double minimum, double maximum) {
	assert(minimum <= maximum);
	double standardSigmoid = 1.0 / (1.0 + pow(e, -x));
	double range = maximum - minimum;
	return minimum + (standardSigmoid * range);
}

double sigmoid(double x) {
	return bounded_sigmoid(x, 0.0, 1.0);
}

double normal_dist(double x, double mean, double variance) {
	assert(variance >= 0);
	double stdDev = sqrt(variance);
	double constant = 1.0 / (stdDev * sqrt(2.0 * pi));
	double exponent = (-1.0 / 2.0) * pow((x - mean) / stdDev, 2);
	return constant * pow(e, exponent);
}

double std_normal_dist(double x) {
	return normal_dist(x, 0.0, 1.0);
}
