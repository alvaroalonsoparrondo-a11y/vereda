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
// Imported from ESBMC regression/esbmc-unix/github_6831_falsify_prepass_reject
// Needs: --falsify-context-bound 1
// RUN: --multi-property --falsify-context-bound 1
// MODE: FUTURE
// EXPECT: ^ERROR: --falsify-context-bound cannot be combined with --multi-property$
