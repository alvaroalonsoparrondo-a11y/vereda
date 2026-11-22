// The base of the snapshotted element is an array directly, not a struct
// member, so the snapshot needs no member re-applied to it.
#define N 4
#define BOUND 100

int g[N];

void bump(void)
{
  unsigned j;
  __ESBMC_requires(
    __ESBMC_forall(&j, !(j < N) || (g[j] > -BOUND && g[j] < BOUND)));
  __ESBMC_ensures(
    __ESBMC_forall(&j, !(j < N) || (g[j] == __ESBMC_old(g[j]) + 1)));

  for (unsigned i = 0; i < N; i++)
    g[i] = g[i] + 1;
}

int main(void)
{
  return 0;
}
// Imported from ESBMC regression/function_contract/github_4219_old_in_forall_array_base
// Needs: --enforce-contract bump
// RUN: --function bump --enforce-contract bump --unwind 8
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
