#include <stdlib.h>
#include <limits.h>
#include "../../src/math_lib.h"

static const double ERROR_TOLERANCE = 1e-10;

#suite MathLib

#test sigmoid_test
	ck_assert_msg(fabs(sigmoid(INT_MIN) - 0) <= ERROR_TOLERANCE, "sigmoid failed at -inf");
	ck_assert_msg(fabs(sigmoid(0) - 0.5) <= ERROR_TOLERANCE, "sigmoid(0) should be 0.5");
	ck_assert_msg(fabs(sigmoid(INT_MAX) - 1) <= ERROR_TOLERANCE, "sigmoid failed at +inf");
	
#test bounded_sigmoid_test
	ck_assert_msg(fabs(bounded_sigmoid(INT_MIN, -10, 10) - (-10)) <= ERROR_TOLERANCE,
		"bounded_sigmoid failed at -inf");
	ck_assert_msg(fabs(bounded_sigmoid(0, 2, 4) - 3) <= ERROR_TOLERANCE,
		"bounded_sigmoid(0, 2, 4) should be 3.0");
	ck_assert_msg(fabs(bounded_sigmoid(INT_MAX, 0, 20) - 20) <= ERROR_TOLERANCE,
		"bounded_sigmoid failed at +inf");
