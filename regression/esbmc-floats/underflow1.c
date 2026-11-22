#include <assert.h>
#include <float.h>
#include <math.h>
 
int main() {
    double x = __VERIFIER_nondet_double();
    double y = __VERIFIER_nondet_double();
 
    __VERIFIER_assume(x > 0.0 && x < 1.0e-154);
    __VERIFIER_assume(y > 0.0 && y < 1.0e-154);
 
    double result = x * y;
 
    // Underflow check
    assert(result > 0.0);  
 
    return 0;
}
// Imported from ESBMC regression/floats/underflow1
// Needs: --ir
// RUN: --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
