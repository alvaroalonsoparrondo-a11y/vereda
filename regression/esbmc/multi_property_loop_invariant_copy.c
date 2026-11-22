/* Both copies --loop-invariant makes of assert(n != 7) are proved. */
#include <assert.h>

unsigned nondet_uint();

int main()
{
  unsigned n = nondet_uint();
  unsigned i = 0;
  __VERIFIER_assume(n != 7);
  __ESBMC_loop_invariant(i <= 10);
  while (i < 10)
  {
    assert(n != 7);
    assert(i < 10);
    i++;
  }
  return 0;
}
// Imported from ESBMC regression/esbmc/multi_property_loop_invariant_copy
// Needs: --loop-invariant --multi-fail-fast 1
// RUN: --loop-invariant --multi-property --multi-fail-fast 1 --max-k-step 2
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
// EXPECT: ^\s+PASSED\s+\[main\.assertion\.3\]\s+line\s+14\s+assertion n != 7$
// EXPECT: ^\s+PASSED\s+\[main\.assertion\.4\]\s+line\s+14\s+assertion n != 7$
