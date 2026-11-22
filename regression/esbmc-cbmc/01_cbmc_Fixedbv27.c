#include <assert.h>

int roundInt(float a) {
  if (a>=0)
    return (int)(a+0.5f);
  else
    return (int)(a-0.5f);
}

void main() {
  float a[1];
	int temp;
	//a[0] = -0.6;
	a[0] = -12.5;
//  printf("%d\n", roundInt(a));
  assert(roundInt(a[0]) == -12.0);
}

// Imported from ESBMC regression/cbmc/01_cbmc_Fixedbv27
// Needs: --fixedbv --ir
// RUN: --fixedbv --no-slice --no-simplify --ir --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
