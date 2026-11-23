#include <string.h>

int main ()
{
  char szInput[256];
  strcpy(szInput, "just testing");
  assert(strlen(szInput) == 12);
  return 0;
}
// Imported from ESBMC regression/cstd/strlen
// RUN: --unwind 13
// EXPECT: ^VERIFICATION SUCCESSFUL$
