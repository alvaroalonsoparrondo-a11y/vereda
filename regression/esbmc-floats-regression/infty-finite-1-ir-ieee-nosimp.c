#include <math.h>
#include <assert.h>

int main()
{
	assert(!isfinite(INFINITY));
}
// Imported from ESBMC regression/floats-regression/infty-finite-1-ir-ieee-nosimp
// Needs: --ir-ieee
// RUN: --ir-ieee --z3 --no-simplify
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
