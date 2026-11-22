#include <string.h>

int main ()
{
  char szInput[256];
  strcpy(szInput, "just testing");
  assert(strlen(szInput) == 10);
  return 0;
}
// Imported from ESBMC regression/cstd/strlen_bug
// RUN: --unwind 13
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^VERIFICATION FAILED$
// MODE: FUTURE
