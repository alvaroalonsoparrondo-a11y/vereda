#include <assert.h>

int main()
{
  assert(__builtin_abs(-3) == 3);
  assert(__builtin_labs(-3l) == -3);
  return 0;
}
// Imported from ESBMC regression/esbmc/builtin_abs_fail
// RUN: --multi-property
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^\*\* 1 of 2 properties failed, 1 passed$
// EXPECT: FAILED\s+\[main.assertion.2\].*__builtin_labs
// Vereda: unmet EXPECT: ^\*\* 1 of 2 properties failed, 1 passed$
// MODE: FUTURE
