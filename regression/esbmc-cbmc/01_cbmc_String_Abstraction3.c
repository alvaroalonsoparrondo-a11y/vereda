#include <assert.h>
#include <string.h>

int main()
{
  char a[100], b[100], *p;

  strcpy(a, "asdasd\000");
  assert(strlen(a+1)==5);
  
  p=a+1;
  assert(strlen(p)==5);

  a[10]=0;
  assert(strlen(a)==6);

  a[3]=0;
  assert(strlen(a)==3);
}
// Imported from ESBMC regression/cbmc/01_cbmc_String_Abstraction3
// RUN: --unwind 101
// EXPECT: ^VERIFICATION SUCCESSFUL$
