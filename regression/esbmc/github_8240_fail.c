#include <assert.h>

/* #8240: an int[4] is 16 bytes, so 8 bytes of it are readable. A pointer with
 * no known object may address one of any size. */
int *nondet_ptr(void);

int main(void)
{
  int a[4];
  assert(__CPROVER_OBJECT_SIZE(a) == 4);
  assert(!__CPROVER_r_ok(a, 8));
  int *p = nondet_ptr();
  assert(__CPROVER_OBJECT_SIZE(p) != 4);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_8240_fail
// RUN: --multi-property
// EXPECT: ^  FAILED .*assertion __CPROVER_OBJECT_SIZE\(a\) == 4$
// EXPECT: ^  FAILED .*assertion !__CPROVER_r_ok\(a, 8\)$
// EXPECT: ^  FAILED .*assertion __CPROVER_OBJECT_SIZE\(p\) != 4$
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^  FAILED .*assertion __CPROVER_OBJECT_SIZE\(a\) == 4$
// MODE: FUTURE
