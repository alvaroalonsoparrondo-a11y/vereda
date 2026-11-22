// p - (p - j) folds to j in ptrdiff_t.
#include <assert.h>
#include <stddef.h>
_Bool nondet_bool(void);
long nondet_long(void);
int nondet_int(void);
int main(void)
{
  int a[8];
  int *p = &a[4];
  int j = nondet_int();
  __VERIFIER_assume(j >= -3 && j <= 4);
  long k = nondet_long();
  ptrdiff_t n = k;
  if (nondet_bool())
    n = p - (p - j);
  assert(n != j);
  return 0;
}
// Imported from ESBMC regression/esbmc/pointer_diff_sub_sub_fail
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^\s+assertion n != j$
// Vereda: unmet EXPECT: ^\s+assertion n != j$
// MODE: FUTURE
