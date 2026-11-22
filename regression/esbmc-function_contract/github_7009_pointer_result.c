/* The result is the only definition of what the call returns, so it is a fresh
 * nondet with no value set. The ensures `== &a` pins it, so the write through p
 * reaches a (#7066).
 *
 * Leaving the result undeclared instead is what #7009 was: the ensures would be
 * assumed about the caller's stale pointer, `p == &a` would be assume-false and
 * everything after the call would pass vacuously. */
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
  __VERIFIER_assert(a == 5); // the write through p reaches a
  return 0;
}
// Imported from ESBMC regression/function_contract/github_7009_pointer_result
// Needs: --replace-call-with-contract pick
// RUN: --replace-call-with-contract pick
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
