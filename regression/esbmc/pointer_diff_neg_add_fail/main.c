// a - (a + j) folds to -j in ptrdiff_t, negated after widening.
#include <assert.h>
#include <stddef.h>
_Bool nondet_bool(void);
long nondet_long(void);
unsigned nondet_uint(void);
int main(void)
{
  int a[8];
  int *p = &a[4];
  unsigned j = nondet_uint();
  __ESBMC_assume(j < 8);
  long k = nondet_long();
  ptrdiff_t n = k;
  if (nondet_bool())
    n = a - (a + j);
  assert(n != -(long)j);
  return 0;
}
// Imported from ESBMC regression/esbmc/pointer_diff_neg_add_fail
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^\s+assertion n != -\(long\)j$
// Vereda: unmet EXPECT: ^\s+assertion n != -\(long\)j$
// MODE: FUTURE
