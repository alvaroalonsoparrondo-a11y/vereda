#include <limits.h>
unsigned __VERIFIER_nondet_uint(void);
int main(void)
{
  unsigned a = __VERIFIER_nondet_uint(), b = __VERIFIER_nondet_uint();
  if (a <= UINT_MAX - b)
    return a + b;
  return 0;
}
// Imported from ESBMC regression/z3/github_9229
// Needs: --unsigned-overflow-check
// RUN: --unsigned-overflow-check --z3
// MODE: FUTURE
// EXPECT: ^  PASSED .*line   7  arithmetic overflow on add$
// EXPECT: ^VERIFICATION SUCCESSFUL$
