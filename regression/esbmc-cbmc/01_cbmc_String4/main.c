#include <string.h>

int main()
{
  assert(strlen("asdasd")==6);
  assert(strlen("")==0);
}
// Imported from ESBMC regression/cbmc/01_cbmc_String4
// RUN: --unwind 7
// EXPECT: ^VERIFICATION SUCCESSFUL$
