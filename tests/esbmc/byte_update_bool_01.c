#include <assert.h>

int main()
{
  _Bool v;
  char *ptr = (char *)&v;
  ptr[0] = 0;
  assert(!v);
  return 0;
}
// Imported from ESBMC regression/esbmc/byte_update_bool_01
// RUN: --unwind 1
// EXPECT: ^VERIFICATION SUCCESSFUL$
