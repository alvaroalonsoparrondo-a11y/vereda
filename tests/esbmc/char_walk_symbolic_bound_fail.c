/* A byte-wise walk to a member element at a nondeterministic index has no
 * constant bound; it is left to unwinding and still counts correctly. */
#include <assert.h>
int __VERIFIER_nondet_int(void);
struct S { int a[3]; int b; };
int main(void)
{
  struct S s;
  int i = __VERIFIER_nondet_int();
  __VERIFIER_assume(i >= 0 && i <= 2);
  int n = 0;
  for (char *p = (char *)&s.a[0]; p != (char *)&s.a[i]; ++p)
    ++n;
  assert(n != 4 * i);
  return 0;
}
// Imported from ESBMC regression/esbmc/char_walk_symbolic_bound_fail
// RUN: --unwind 9
// EXPECT: ^VERIFICATION FAILED$
