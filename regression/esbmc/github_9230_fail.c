// #9230: a pointer cast to _Bool reaching the solver is true for non-NULL.
#include <assert.h>

int nondet_int();

int main()
{
  int x;
  int *p = nondet_int() ? &x : 0;
  _Bool b = (_Bool)p;
  assert(b == (p == 0));
  return 0;
}
// Imported from ESBMC regression/esbmc/github_9230_fail
// EXPECT: ^\s*assertion b == \(p == 0\)$
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^\s*assertion b == \(p == 0\)$
// MODE: FUTURE
