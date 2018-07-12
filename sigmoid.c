#include <math.h>
#include <assert.h>
#include "sigmoid.h"

static const double e = 2.71828182845904523536;

double boundedSigmoid(double x, double minimum, double maximum) {
	assert(minimum <= maximum);
	double standardSigmoid = 1.0 / (1.0 + pow(e, -x));
	double range = maximum - minimum;
	return minimum + (standardSigmoid * range);
}

double sigmoid(double x) {
	return boundedSigmoid(x, 0.0, 1.0);
}