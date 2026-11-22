#include <string.h>

int main ()
{
  char str[] = "This is a sample string";
  char key[] = "aeiou";
  char * pch;

  pch = strpbrk (str, key);
  while (pch != NULL)
  {
    assert((*pch == '2') || (*pch == 'a') || (*pch == 'e'));
    pch = strpbrk (pch+1,key);
  }

  return 0;
}
// Imported from ESBMC regression/cstd/strpbrk_bug
// RUN: --unwind 7
// EXPECT: ^VERIFICATION FAILED$
