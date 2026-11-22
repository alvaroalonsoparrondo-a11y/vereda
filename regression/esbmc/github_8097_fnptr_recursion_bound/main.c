/* #8097: a function-pointer call whose first target stops at the recursion
 * bound must still run the remaining targets. */
#include <assert.h>
int nondet_int();
int f3(void *p)
{
  return 1;
}
int f2(int (*a)(void *))
{
  int r = a(f3);
  assert(r == 1);
  return r;
}
int main()
{
  int (*b)(void *) = nondet_int() ? (int (*)(void *))f3 : (int (*)(void *))f2;
  return f2(b);
}
// Imported from ESBMC regression/esbmc/github_8097_fnptr_recursion_bound
// RUN: --unwind 1 --no-unwinding-assertions
// EXPECT: ^VERIFICATION SUCCESSFUL$
// Vereda: unmet EXPECT: ^VERIFICATION SUCCESSFUL$
// MODE: FUTURE
