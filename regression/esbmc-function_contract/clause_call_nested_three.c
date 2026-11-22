// clause_call_nested with a third level. The data dependency fixes the order
// the calls are reached in, so the diagnostic has one right answer; with three
// candidates an ordering that is not the program's is unlikely to agree with it
// by chance.
int innermost(int x)
{
  return x;
}
int middle(int x)
{
  return x;
}
int outermost(int x)
{
  return x;
}

int f(int x)
{
  __ESBMC_requires(outermost(middle(innermost(x))) > 100);
  __ESBMC_ensures(__ESBMC_return_value > 100);
  return x;
}

int main(void)
{
  int n;
  __VERIFIER_assume(n > 200);
  return f(n);
}
// Imported from ESBMC regression/function_contract/clause_call_nested_three
// Needs: --enforce-contract f
// RUN: --enforce-contract f --function f
// MODE: FUTURE
// EXPECT: ^ERROR: --enforce-contract: cannot use 'f': a contract clause calls 'c:@F@innermost', whose result the clause cannot name outside the function body$
