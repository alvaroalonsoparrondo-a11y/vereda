#include <assert.h>
#include <float.h>
#include <math.h>

int main() 
{
    double x = nondet_double();
    double y = nondet_double();

    __ESBMC_assume(x > 0.0 && x < 1.0e-154);
    __ESBMC_assume(y > 0.0 && y < 1.0e-154);

    double result = x * y;

    // Underflow check
    assert(result > 0.0);

    return 0;
}
// Imported from ESBMC regression/floats/underflow17
// Needs: --ir
// RUN: --ir
// MODE: FUTURE
// EXPECT: ^  result = 0\.000000$
// EXPECT: ^VERIFICATION FAILED$
