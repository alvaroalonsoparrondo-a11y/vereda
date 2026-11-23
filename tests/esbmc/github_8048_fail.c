/* #8048: a VLA declared on a path not taken must not rule out the paths where
 * its bound is negative. */
#include <assert.h>
int __VERIFIER_nondet_int(void);
int main()
{
  int n = __VERIFIER_nondet_int();
  if (n > 1)
  {
    int a[n];
  }
  assert(n != -1);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_8048_fail
// RUN: --multi-property
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^\s+FAILED\s+\[main\.assertion\.\d+\]\s+line 12\s+assertion n != -1$
// Vereda: unmet EXPECT: ^\s+FAILED\s+\[main\.assertion\.\d+\]\s+line 12\s+assertion n != -1$
// MODE: FUTURE
