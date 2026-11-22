#include <stdio.h>

int main(int argc, char *argv[])
{
  char *toParseStr = (char *)malloc(11);
  printf("Enter string here: ");
  scanf("%10s", toParseStr);
  printf("%s", toParseStr);
  free(toParseStr);
}
// Imported from ESBMC regression/cstd/scanf_malloc_2
// Needs: --overflow-check
// RUN: --overflow-check -Wno-error=implicit-function-declaration --force-malloc-success
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
