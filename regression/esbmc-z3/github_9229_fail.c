#include <limits.h>
unsigned nondet_uint(void);
int main(void)
{
  unsigned a = nondet_uint(), b = nondet_uint();
  if (a >= UINT_MAX - b)
    return a + b;
  return 0;
}
// Imported from ESBMC regression/z3/github_9229_fail
// Needs: --unsigned-overflow-check
// RUN: --unsigned-overflow-check --z3
// MODE: FUTURE
// EXPECT: ^  !overflow\("\+", a, b\)$
// EXPECT: ^VERIFICATION FAILED$
