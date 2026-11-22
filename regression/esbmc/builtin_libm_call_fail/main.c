#include <assert.h>

int main(void)
{
  int e = 0;
  __builtin_frexp(8.0, &e);
  assert(e == 0);
  return 0;
}
// Imported from ESBMC regression/esbmc/builtin_libm_call_fail
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: assertion e == 0
// Vereda: unmet EXPECT: assertion e == 0
// MODE: FUTURE
