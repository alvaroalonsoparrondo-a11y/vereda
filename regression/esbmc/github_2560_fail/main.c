#include <assert.h>
int main()
{
  float f;
  double d;
  unsigned char x;

  d = f;

  if (f == x)
    assert(d != x);
}
// Imported from ESBMC regression/esbmc/github_2560_fail
// Needs: --ir
// RUN: --z3 --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
