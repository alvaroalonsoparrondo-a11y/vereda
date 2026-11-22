#include <math.h>
#include <assert.h>

int main()
{
	double inf = 1.0 / 0.0;
	assert(inf == INFINITY);
	assert(!isfinite(inf));
}
// Imported from ESBMC regression/floats-regression/infty-finite-ir-ieee-nosimp
// Needs: --ir-ieee
// RUN: --ir-ieee --z3 --no-simplify
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
