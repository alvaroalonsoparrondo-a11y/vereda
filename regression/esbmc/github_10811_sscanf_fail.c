#include <assert.h>
#include <stdio.h>

/* #10811: only the object p points to may be written. */
_Bool nondet_bool(void);
int a[2] = {1, 2};
int b[2];

int main()
{
  int *p = nondet_bool() ? a : b;
  __VERIFIER_assume(p == a);
  sscanf("5", "%d", p);
  assert(a[0] == 1);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_10811_sscanf_fail
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^  assertion a\[0\] == 1$
// Vereda: unmet EXPECT: ^VERIFICATION FAILED$
// MODE: FUTURE
