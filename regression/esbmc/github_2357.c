#include <assert.h>

int main()
{
  int x = 2147483648ULL;
  assert(x == 2147483648ULL);
}
// Imported from ESBMC regression/esbmc/github_2357
// Needs: --ir --overflow-check
// RUN: --z3 --ir --overflow-check --no-simplify
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
