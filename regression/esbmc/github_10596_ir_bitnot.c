// Under --ir integers are unbounded, so ~b must be -b - 1 for every b, not
// the 64-bit complement (#10596). --no-simplify keeps the simplifier from
// rewriting ~b + 1 as -b before the solver sees it.
unsigned nondet_uint(void);
long long nondet_longlong(void);

int main(void)
{
  unsigned b = nondet_uint();
  __VERIFIER_assume(b <= 10);
  unsigned y = ~b + 1u;
  __VERIFIER_assert(y + b == 0); // ~b + 1 == -b

  long long x = nondet_longlong();
  __VERIFIER_assert(~x == -x - 1); // ~x == -x - 1
  return 0;
}
// Imported from ESBMC regression/esbmc/github_10596_ir_bitnot
// Needs: --ir
// RUN: --z3 --ir --no-simplify
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
