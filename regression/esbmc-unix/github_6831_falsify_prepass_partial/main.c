#include <assert.h>

int nondet_int();

int main()
{
  int n = nondet_int();
  __ESBMC_assume(n == 3);

  int i = 0;
  while (i < n)
    i++;

  assert(i == n);
  return 0;
}
// Imported from ESBMC regression/esbmc-unix/github_6831_falsify_prepass_partial
// Needs: --partial-loops --falsify-context-bound 1
// RUN: --partial-loops --falsify-context-bound 1
// MODE: FUTURE
// EXPECT: ^Falsifying with context bound 1$
// EXPECT: ^VERIFICATION SUCCESSFUL$
