#include <string.h>
#include <stdio.h>

int main()
{
  char buffer[100];
  unsigned int i;
  if(fgets(buffer, 100, stdin) != 0)
    i = strlen(buffer);
  return 0;
}
// Imported from ESBMC regression/esbmc-unix2/github_508_safe
// RUN: --unwind 101
// MODE: THOROUGH
// EXPECT: ^VERIFICATION SUCCESSFUL$
