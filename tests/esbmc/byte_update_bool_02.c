#include <assert.h>

int main()
{
  _Bool v = 1;
  char *ptr = (char *)&v;
  ptr[0] = 0;
  assert(v);
  return 0;
}
// Imported from ESBMC regression/esbmc/byte_update_bool_02
// RUN: --no-unwinding-assertions --unwind 1
// EXPECT: ^VERIFICATION FAILED$
