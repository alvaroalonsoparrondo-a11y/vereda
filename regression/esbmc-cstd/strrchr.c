#include <string.h>

int main ()
{
  char str[] = "This is a sample string";
  char * pch;
  pch=strrchr(str,'s');
  assert((pch-str+1) == 18);
  return 0;
}
// Imported from ESBMC regression/cstd/strrchr
// RUN: --unwind 7
// EXPECT: ^VERIFICATION SUCCESSFUL$
