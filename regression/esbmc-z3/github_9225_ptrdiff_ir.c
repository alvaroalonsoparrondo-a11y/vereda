/* github #9225: under --ir a pointer difference still divides, truncating
 * toward zero, for power-of-two and other element sizes alike. */
#include <assert.h>

unsigned __VERIFIER_nondet_uint(void);
int a[10];
struct s
{
  int a, b, c;
} st[10];

int main(void)
{
  unsigned i = __VERIFIER_nondet_uint();
  __VERIFIER_assume(i < 10);
  assert(&a[i] - a == i);
  assert(a - &a[i] == -(long)i);
  assert(&st[i] - st == i);
  assert(st - &st[i] == -(long)i);

  /* 18 bytes is one and a half 12-byte elements: +-1.5 truncates to +-1. */
  struct s *q = (struct s *)((char *)st + 18);
  assert(q - st == 1);
  assert(st - q == -1);
  return 0;
}
// Imported from ESBMC regression/z3/github_9225_ptrdiff_ir
// Needs: --ir
// RUN: --ir --z3 --64
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
