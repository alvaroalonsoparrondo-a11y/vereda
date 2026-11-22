// Anti-vacuity twin: the surviving write must carry the value it wrote.
#include <assert.h>

int main(void)
{
  int r[2][2];
  _Bool c = nondet_bool();

  __ESBMC_assume(c);
  if (c)
  {
    r[0][0] = 1;
    r[0][1] = 2;
  }

  assert(r[0][0] == 2);
  return 0;
}
// Imported from ESBMC regression/esbmc/multidim_const_array_write_kept_fail
// EXPECT: ^VERIFICATION FAILED$
