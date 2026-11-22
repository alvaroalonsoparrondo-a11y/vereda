#include <assert.h>

extern long double __VERIFIER_nondet_long_double(void);

int main(void)
{
  long double x = __VERIFIER_nondet_long_double();
  assert(x != x + 0.0L);
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-nondet-long-double-trace
// Needs: --ir-ieee --i386-linux
// RUN: --ir-ieee --z3 --i386-linux
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
