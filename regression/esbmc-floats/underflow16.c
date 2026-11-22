#include <assert.h>

int main() 
{
    double x = -1e-200;
    double y = -1e-200;
    double result = x * y; // Should be positive due to sign rules
    
    assert(result > 0.0); // (-) * (-) = (+), but may underflow to 0
    return 0;
}
// Imported from ESBMC regression/floats/underflow16
// Needs: --ir
// RUN: --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
