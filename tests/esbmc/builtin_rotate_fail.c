#include <assert.h>

int main()
{
  assert(__builtin_rotateleft32(0x80000001u, 1) == 3);
  assert(__builtin_rotateright32(0x80000001u, 1) == 3);
  return 0;
}
// Imported from ESBMC regression/esbmc/builtin_rotate_fail
// RUN: --multi-property
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^\*\* 1 of 2 properties failed, 1 passed$
// EXPECT: FAILED\s+\[main.assertion.2\].*__builtin_rotateright32
// Vereda: unmet EXPECT: ^\*\* 1 of 2 properties failed, 1 passed$
// MODE: FUTURE
