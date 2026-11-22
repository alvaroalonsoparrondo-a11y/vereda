#include <string.h>

int main ()
{
  char str[80];
  strcpy (str,"these ");
  strcat (str,"strings ");
  strcat (str,"are ");
  strcat (str,"concatenated.");

  assert(!strcmp("these strings are concatenated.", str));

  return 0;
}
// Imported from ESBMC regression/cstd/strcat
// RUN: --unwind 32
// EXPECT: ^VERIFICATION SUCCESSFUL$
