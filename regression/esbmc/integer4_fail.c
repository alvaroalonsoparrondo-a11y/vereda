#include <assert.h>

int main() {
  int a = __VERIFIER_nondet_int();
  int b = __VERIFIER_nondet_int();

  __VERIFIER_assume(a > 0 && b > 0);

  assert((a * b) > 0);
}
// Imported from ESBMC regression/esbmc/integer4_fail
// Needs: --ir --overflow-check
// RUN: --z3 --ir --overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
