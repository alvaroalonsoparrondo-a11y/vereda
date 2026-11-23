#include <stdio.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
  int x;
  long long y;
  char z[10];

  scanf("%10d%19ld%9s", &x, &y, z);

  return 0;
}
// Imported from ESBMC regression/cstd/scanf-true
// Needs: --overflow-check
// RUN: --overflow-check --64
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
