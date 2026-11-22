/* Regression test: enforce-contract + loop-invariant (passing case)
 * Verifies that --enforce-contract correctly checks a function whose loop
 * invariant is strong enough to prove the postcondition.
 *
 * Invariant: i >= 0 && i <= n
 * At loop exit (i >= n): i == n, so return_value == n.  ensures holds.
 */
extern int __VERIFIER_nondet_int(void);

int count_to(int n)
{
  __ESBMC_requires(n >= 0 && n <= 10);
  __ESBMC_ensures(__ESBMC_return_value == n);

  int i = 0;
  __ESBMC_loop_invariant(i >= 0 && i <= n);
  while(i < n)
    i++;
  return i;
}

int main()
{
  int n = __VERIFIER_nondet_int();
  __VERIFIER_assume(n >= 0 && n <= 10);
  count_to(n);
  return 0;
}
// Imported from ESBMC regression/function_contract/enforce_loop_inv_count_pass
// Needs: --enforce-contract count_to --loop-invariant-check
// RUN: --enforce-contract count_to --loop-invariant-check
// MODE: FUTURE
// EXPECT: ^Processing 1 loop invariant$
// EXPECT: ^VERIFICATION SUCCESSFUL$
