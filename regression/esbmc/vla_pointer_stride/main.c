#include <assert.h>
int nondet_int(void);
int main(void)
{
  int m = nondet_int();
  __ESBMC_assume(m >= 1 && m <= 4);
  int a[3][m];
  a[2][m - 1] = 7;
  int (*p)[m] = a + 2;
  int (*q)[m] = a;
  assert(p - q == 2);
  assert((*p)[m - 1] == 7);
  return 0;
}
// Imported from ESBMC regression/esbmc/vla_pointer_stride
// EXPECT: ^VERIFICATION SUCCESSFUL$
// Vereda: unmet EXPECT: ^VERIFICATION SUCCESSFUL$
// MODE: FUTURE
