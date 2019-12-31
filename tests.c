#include <stdio.h>
#include <math.h>

#include "strtodouble.h"

#define EPSILON 1e-15

#define TEST_ASSERT(x,y) _test_assert((x), (y), __LINE__)

static int tests_total  = 0;
static int tests_failed = 0;

static void _test_assert(double x, double y, int line)
{
    tests_total++;

    if(isnan(x) && isnan(y)) return;
    if(isinf(x) && isinf(y) && x > 0 && y > 0) return;
    if(isinf(x) && isinf(y) && x < 0 && y > 0) return;
    if(x == y) return;
    if(fabs(1-x/y) < EPSILON) return;

    tests_failed++;
    fprintf(stderr, "line %d: %g != %g", line, x, y);
}

int main(void)
{
    // NANs and infinities
    TEST_ASSERT(NAN, strtodouble("NaN", NULL));
    TEST_ASSERT(INFINITY, strtodouble("INF", NULL));
    TEST_ASSERT(-INFINITY, strtodouble("-INf", NULL));

    // 0
    TEST_ASSERT(0, strtodouble("0", NULL));
    TEST_ASSERT(0, strtodouble("0.", NULL));
    TEST_ASSERT(0, strtodouble("0.0", NULL));
    TEST_ASSERT(0, strtodouble(".0", NULL));
    TEST_ASSERT(0, strtodouble(".0000", NULL));
    TEST_ASSERT(0, strtodouble("0.0000", NULL));
    TEST_ASSERT(0, strtodouble("00000.0000", NULL));
    TEST_ASSERT(0, strtodouble("+0", NULL));
    TEST_ASSERT(0, strtodouble("+0.", NULL));
    TEST_ASSERT(0, strtodouble("+0.0", NULL));
    TEST_ASSERT(0, strtodouble("+.0", NULL));
    TEST_ASSERT(0, strtodouble("+.0000", NULL));
    TEST_ASSERT(0, strtodouble("+0.0000", NULL));
    TEST_ASSERT(0, strtodouble("+00000.0000", NULL));
    TEST_ASSERT(0, strtodouble("-0", NULL));
    TEST_ASSERT(0, strtodouble("-0.", NULL));
    TEST_ASSERT(0, strtodouble("-0.0", NULL));
    TEST_ASSERT(0, strtodouble("-.0", NULL));
    TEST_ASSERT(0, strtodouble("-.0000", NULL));
    TEST_ASSERT(0, strtodouble("-0.0000", NULL));
    TEST_ASSERT(0, strtodouble("-00000.0000", NULL));
    TEST_ASSERT(0, strtodouble("0e0", NULL));
    TEST_ASSERT(0, strtodouble("0.e0", NULL));
    TEST_ASSERT(0, strtodouble("0.e10", NULL));
    TEST_ASSERT(0, strtodouble("0.e-10", NULL));
    TEST_ASSERT(0, strtodouble("-0e0", NULL));
    TEST_ASSERT(0, strtodouble("-0.e0", NULL));
    TEST_ASSERT(0, strtodouble("-0.e10", NULL));
    TEST_ASSERT(0, strtodouble("-0.e-10", NULL));

    // 1
    TEST_ASSERT(1, strtodouble("1", NULL));
    TEST_ASSERT(1, strtodouble("1e0", NULL));

    // positive number
    TEST_ASSERT(1.234, strtodouble("1.234", NULL));
    TEST_ASSERT(1.234, strtodouble("+1.234", NULL));
    TEST_ASSERT(1.234, strtodouble("+00001.234", NULL));
    TEST_ASSERT(1.234, strtodouble("12.34e-1", NULL));
    TEST_ASSERT(1.234, strtodouble("12.34e-0001", NULL));
    TEST_ASSERT(1.234, strtodouble("0.1234e1", NULL));
    TEST_ASSERT(1.234, strtodouble("0.1234e+1", NULL));
    TEST_ASSERT(1.234, strtodouble("0.1234e+0001", NULL));
    TEST_ASSERT(1.234, strtodouble(".1234e1", NULL));
    TEST_ASSERT(1.234, strtodouble(".1234e+1", NULL));
    TEST_ASSERT(1.234, strtodouble(".1234e+0001", NULL));

    // negative number
    TEST_ASSERT(-1.234, strtodouble("-1.234", NULL));
    TEST_ASSERT(-1.234, strtodouble("-1.234", NULL));
    TEST_ASSERT(-1.234, strtodouble("-00001.234", NULL));
    TEST_ASSERT(-1.234, strtodouble("-12.34e-1", NULL));
    TEST_ASSERT(-1.234, strtodouble("-12.34e-0001", NULL));
    TEST_ASSERT(-1.234, strtodouble("-0.1234e1", NULL));
    TEST_ASSERT(-1.234, strtodouble("-0.1234e+1", NULL));
    TEST_ASSERT(-1.234, strtodouble("-0.1234e+0001", NULL));
    TEST_ASSERT(-1.234, strtodouble("-.1234e1", NULL));
    TEST_ASSERT(-1.234, strtodouble("-.1234e+1", NULL));
    TEST_ASSERT(-1.234, strtodouble("-.1234e+0001", NULL));

    // trailing characters
    TEST_ASSERT(1.234, strtodouble("1.234exx", NULL));
    TEST_ASSERT(1.234, strtodouble("1.234e0xx", NULL));
    TEST_ASSERT(1.234, strtodouble(".1234e1xx", NULL));
    TEST_ASSERT(1.234, strtodouble(".1234e1e1", NULL));

    // whitespace
    TEST_ASSERT(1.234, strtodouble(" 1.234", NULL));
    TEST_ASSERT(1.234, strtodouble("   1.234", NULL));
    TEST_ASSERT(1.234, strtodouble("\r1.234", NULL));
    TEST_ASSERT(1.234, strtodouble("\n1.234", NULL));
    TEST_ASSERT(1.234, strtodouble("\t1.234", NULL));
    TEST_ASSERT(1.234, strtodouble(" \r\n\t1.234", NULL));

    // overflow
    TEST_ASSERT(INFINITY, strtodouble("1e1000", NULL));
    TEST_ASSERT(-INFINITY, strtodouble("-1e1000", NULL));

    // underflow
    TEST_ASSERT(0, strtodouble("1e-1000", NULL));
    TEST_ASSERT(0, strtodouble("-1e-1000", NULL));

    // invalid format
    TEST_ASSERT(NAN, strtodouble("-e-1", NULL));
    TEST_ASSERT(NAN, strtodouble("e1", NULL));
    TEST_ASSERT(NAN, strtodouble("+e1", NULL));
    TEST_ASSERT(NAN, strtodouble("-e1", NULL));
    TEST_ASSERT(NAN, strtodouble("foobar", NULL));

    if(tests_failed == 0)
        printf("Passed all %d test cases\n", tests_total);
    else
        printf("Passed %d of %d test cases\n", tests_total-tests_failed, tests_total);

    return 0;
}
