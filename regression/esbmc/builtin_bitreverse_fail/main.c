#include <assert.h>

int main()
{
  assert(__builtin_bitreverse16(0x1234) == 0x2c48);
  assert(__builtin_bitreverse16(0x1234) == 0x4321);
  return 0;
}
// Imported from ESBMC regression/esbmc/builtin_bitreverse_fail
// RUN: --multi-property
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^\*\* 1 of 2 properties failed, 1 passed$
// EXPECT: FAILED\s+\[main.assertion.2\].*__builtin_bitreverse16
// Vereda: unmet EXPECT: ^\*\* 1 of 2 properties failed, 1 passed$
// MODE: FUTURE
