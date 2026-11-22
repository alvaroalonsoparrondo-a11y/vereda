#include <assert.h>
extern double __VERIFIER_nondet_double(void);
int main(void)
{
  double x = __VERIFIER_nondet_double();
  double y = __VERIFIER_nondet_double();
  double z = x + y;
  assert(z != x + y);
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-rounding-nearest-tight-bounds
// Needs: --ir-ieee
// RUN: --ir-ieee --z3 --smt-formula-too
// MODE: FUTURE
// EXPECT: \(declare-fun \|smt_conv::ra_lo::[0-9]+\| \(\) Real\)
// EXPECT: \(declare-fun \|smt_conv::ra_hi::[0-9]+\| \(\) Real\)
// EXPECT: \(ite
// EXPECT: 5551115123125783
// EXPECT: ^VERIFICATION FAILED$
