#include <assert.h>

int nondet_int(void);
int x, y;

int main()
{
  int *p = nondet_int() ? &x : &y;
  void *v = &p;
  double d = *(double *)v;
  double e = *(double *)&p;
  assert(d != d);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_4780_pointer_bits_as_double_fail
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^VERIFICATION FAILED$
// MODE: FUTURE
