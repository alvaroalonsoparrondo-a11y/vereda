// The same pointer used both as a bare __ESBMC_old(r) (pointer-value
// snapshot) and as a region __ESBMC_old(r[j]) in one contract is ambiguous
// to materialize -- one shared temp, two incompatible treatments. Rejected
// with a specific diagnostic rather than silently picking one (#7057).
#define N 4

void bump(int r[N])
{
  unsigned j;
  __ESBMC_requires(__ESBMC_is_fresh(r, N * sizeof(int)));
  __ESBMC_ensures(
    __ESBMC_forall(&j, !(j < N) || (r[j] == __ESBMC_old(r[j]) + 1)) &&
    __ESBMC_old(r) == __ESBMC_old(r));
  __ESBMC_assigns(r);

  for (unsigned i = 0; i < N; i++)
    r[i] = r[i] + 1;
}

int main(void)
{
  return 0;
}
// Imported from ESBMC regression/function_contract/github_4219_old_in_forall_array_param_ambiguous_fail
// Needs: --enforce-contract bump
// RUN: --function bump --enforce-contract bump --unwind 8
// MODE: FUTURE
// EXPECT: is used both as a whole-pointer snapshot and as a per-element __ESBMC_old
