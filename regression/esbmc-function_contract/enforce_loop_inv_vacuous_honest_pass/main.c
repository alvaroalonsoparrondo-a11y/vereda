/* Confirm the vacuity probe does NOT misclassify an honest, terminating
 * loop with a sound invariant. The post-loop state (i == n) is reachable,
 * so the probe finds the path satisfiable and the verdict remains
 * VERIFICATION SUCCESSFUL.
 */
extern int __VERIFIER_nondet_int(void);

int count_to(int n)
{
  __ESBMC_requires(n >= 0 && n <= 10);
  __ESBMC_ensures(__ESBMC_return_value == n);

  int i = 0;
  __ESBMC_loop_invariant(i >= 0 && i <= n);
  while (i < n)
    i++;
  return i;
}

int main()
{
  int n = __VERIFIER_nondet_int();
  __ESBMC_assume(n >= 0 && n <= 10);
  count_to(n);
  return 0;
}
// Imported from ESBMC regression/function_contract/enforce_loop_inv_vacuous_honest_pass
// Needs: --enforce-contract count_to --loop-invariant-check
// RUN: --enforce-contract count_to --loop-invariant-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
