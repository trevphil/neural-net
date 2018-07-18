#include <math.h>
#include <assert.h>
#include "math_lib.h"

static const double e = 2.71828182845904523536;

double bounded_sigmoid(double x, double minimum, double maximum) {
	assert(minimum <= maximum);
	double standardSigmoid = 1.0 / (1.0 + pow(e, -x));
	double range = maximum - minimum;
	return minimum + (standardSigmoid * range);
}

double sigmoid(double x) {
	return bounded_sigmoid(x, 0.0, 1.0);
}