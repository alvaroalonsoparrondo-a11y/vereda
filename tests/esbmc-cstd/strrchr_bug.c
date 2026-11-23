#include <string.h>

int main ()
{
  char str[] = "This is a sample string";
  char * pch;
  pch=strrchr(str,'s');
  assert((pch-str+1) == 11);
  return 0;
}
// Imported from ESBMC regression/cstd/strrchr_bug
// RUN: --unwind 7
// EXPECT: ^VERIFICATION FAILED$
