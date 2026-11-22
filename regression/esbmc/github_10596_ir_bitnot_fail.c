// The dual of ../github_10596_ir_bitnot: ~x is -x - 1, never -x.
long long nondet_longlong(void);

int main(void)
{
  long long x = nondet_longlong();
  __VERIFIER_assert(~x == -x); // ~x == -x
  return 0;
}
// Imported from ESBMC regression/esbmc/github_10596_ir_bitnot_fail
// Needs: --ir
// RUN: --z3 --ir --no-simplify
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
