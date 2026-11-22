#include <assert.h>

int main() {
  int a = __VERIFIER_nondet_int();
  int b = __VERIFIER_nondet_int();

  __VERIFIER_assume(a > 0 && b > 0);

  assert((a + b) > 0);
}
// Imported from ESBMC regression/esbmc/integer1
// Needs: --ir
// RUN: --z3 --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
