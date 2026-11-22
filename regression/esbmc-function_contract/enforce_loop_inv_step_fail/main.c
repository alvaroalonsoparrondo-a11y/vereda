/* Regression test: enforce-contract + loop-invariant (inductive-step violation)
 * The invariant i <= n-1 is not preserved: when i == n-1 the loop
 * continues (i < n), and after i++ we get i == n which violates i <= n-1.
 */
int wrong_step(int n)
{
  __ESBMC_requires(n >= 1 && n <= 10);
  __ESBMC_ensures(__ESBMC_return_value == n);

  int i = 0;
  __ESBMC_loop_invariant(i >= 0 && i <= n - 1); /* WRONG: not preserved when i == n-1 */
  while(i < n)
    i++;
  return i;
}

int main()
{
  wrong_step(5);
  return 0;
}
// Imported from ESBMC regression/function_contract/enforce_loop_inv_step_fail
// Needs: --enforce-contract wrong_step --loop-invariant
// RUN: --enforce-contract wrong_step --loop-invariant
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
