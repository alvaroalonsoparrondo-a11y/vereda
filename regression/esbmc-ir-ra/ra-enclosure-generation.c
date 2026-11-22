#include <assert.h>

extern double __VERIFIER_nondet_double(void);

int main() {
  double x = __VERIFIER_nondet_double();
  double y = __VERIFIER_nondet_double();
  double z = x + y;


  assert(z > x);
}
// Imported from ESBMC regression/ir-ra/ra-enclosure-generation
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
