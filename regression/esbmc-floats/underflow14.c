#include <assert.h>
#include <float.h>

int main() 
{
    double subnormal = DBL_TRUE_MIN * 100;
    double large = 1e+100;
    double result = subnormal / large;
    
    assert(result > 0.0); // Likely underflows to zero
    return 0;
}
// Imported from ESBMC regression/floats/underflow14
// Needs: --ir
// RUN: --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
