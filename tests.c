#include <stdio.h>
#include <math.h>

#include "strtodouble.h"

#define EPSILON 1e-15

static int tests = 0;

#define TEST_ASSERT(x_,y_) \
    do { \
        tests++; \
        double x = x_, y = y_; \
        if(isnan(x) && isnan(y)) break; \
        if(isinf(x) && isinf(y) && x > 0 && y > 0) break; \
        if(isinf(x) && isinf(y) && x < 0 && y > 0) break; \
        if(x == y) break; \
        if(fabs(1-x/y) < EPSILON) break; \
        fprintf(stderr, "line %d: %g == %g", __LINE__, x, y); \
        return 1; \
    } while(0)

int main(void)
{
    TEST_ASSERT(NAN, strtodouble("NaN", NULL));
    TEST_ASSERT(INFINITY, strtodouble("INF", NULL));
    TEST_ASSERT(-INFINITY, strtodouble("-INf", NULL));

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

    TEST_ASSERT(1.234, strtodouble("1.234", NULL));
    TEST_ASSERT(1.234, strtodouble("+1.234", NULL));
    TEST_ASSERT(1.234, strtodouble("+00001.234", NULL));
    TEST_ASSERT(1.234, strtodouble("12.34e-1", NULL));
    TEST_ASSERT(1.234, strtodouble("12.34e-0001", NULL));
    TEST_ASSERT(1.234, strtodouble("0.1234e1", NULL));
    TEST_ASSERT(1.234, strtodouble("0.1234e+1", NULL));
    TEST_ASSERT(1.234, strtodouble("0.1234e+0001", NULL));

    printf("Successfully passed %d test cases\n", tests);

    return 0;
}
