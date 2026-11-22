#include <assert.h>
#include <float.h>

int main() 
{
    double subnormal1 = DBL_TRUE_MIN * 2;
    double subnormal2 = DBL_TRUE_MIN * 3;
    double result = subnormal1 * subnormal2;
    
    assert(result > 0.0); // May underflow to zero
    return 0;
}

// Imported from ESBMC regression/floats/underflow13
// Needs: --ir
// RUN: --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
