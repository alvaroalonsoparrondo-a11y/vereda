int nondet_int(void);

int main(void)
{
  int x = nondet_int();
  __VERIFIER_assume(x + 2 == -3);
  __VERIFIER_assert(x == -5); // x is -5
  return 0;
}
// Imported from ESBMC regression/cvc/github_2356_successful
// Needs: --ir
// RUN: --cvc5 --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
