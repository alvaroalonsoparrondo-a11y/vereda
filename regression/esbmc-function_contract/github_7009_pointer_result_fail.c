/* The ensures pins the result to &a, so the write reaches a: a is 5, not 6
 * (#7066). */
int a;

int *pick(int c)
{
  __ESBMC_requires(c == 0);
  __ESBMC_ensures(__ESBMC_return_value == &a);

  return &a;
}

int main(void)
{
  int *p = 0;
  p = pick(0);
  __VERIFIER_assert(p == &a); // pointer equality holds
  *p = 5;
  __VERIFIER_assert(a == 6); // the write through p reaches a
  return 0;
}
// Imported from ESBMC regression/function_contract/github_7009_pointer_result_fail
// Needs: --replace-call-with-contract pick
// RUN: --replace-call-with-contract pick
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^  the write through p reaches a$
