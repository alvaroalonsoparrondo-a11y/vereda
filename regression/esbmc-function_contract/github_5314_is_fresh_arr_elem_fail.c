/* github #5314 soundness guard: the witness index still ranges over the whole
 * is_fresh buffer, so a write to an element NOT in the assigns clause (here a[9],
 * the last valid element) must still be reported as a frame violation. */
__ESBMC_contract
void f(int *a)
{
  __ESBMC_requires(__ESBMC_is_fresh(a, 10 * sizeof(int)));
  __ESBMC_assigns(a[0]);
  a[0] = 0;
  a[9] = 5; /* not in assigns clause */
}
// Imported from ESBMC regression/function_contract/github_5314_is_fresh_arr_elem_fail
// Needs: --enforce-contract f
// RUN: --function f --enforce-contract f
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
