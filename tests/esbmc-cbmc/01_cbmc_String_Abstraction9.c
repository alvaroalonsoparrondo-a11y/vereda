#include <string.h>

void f(char *a, char *b)
{
  strcpy(a, b);
}

int main()
{
  char a[100], b[100], *p;
  
  f(a, "asd");
  assert(strlen(a)==3);
  
  a[2]=0;
  assert(strlen(a)==2);
  
  f(b, a);
  assert(strlen(b)==2);  
}
// Imported from ESBMC regression/cbmc/01_cbmc_String_Abstraction9
// RUN: --unwind 10
// EXPECT: ^VERIFICATION SUCCESSFUL$
