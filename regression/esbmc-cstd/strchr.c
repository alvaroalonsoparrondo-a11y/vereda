#include <string.h>
#include <assert.h>

int main ()
{
  char str[] = "This is a sample string";
  char * pch;

  pch=strchr(str,'s');
  while (pch!=NULL)
  {
    assert(((pch-str+1) == 4) || ((pch-str+1) == 7) || ((pch-str+1) == 11) || ((pch-str+1) == 18));
    pch=strchr(pch+1,'s');
  }
  return 0;
}
// Imported from ESBMC regression/cstd/strchr
// RUN: --unwind 7
// EXPECT: ^VERIFICATION SUCCESSFUL$
// Vereda: unmet EXPECT: ^VERIFICATION SUCCESSFUL$
// MODE: FUTURE
