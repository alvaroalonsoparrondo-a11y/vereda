/* Two independent loops, each tracked separately by the interval domain. */
int main()
{
  int i, j;
  __ESBMC_assume(i >= 0);
  __ESBMC_assume(j >= 0);
  while (i < 3)
    ++i;
  while (j < 4)
    ++j;
  __ESBMC_assert(i >= 3 && j >= 4, "both bounds must be met");
  return 0;
}
// Imported from ESBMC regression/esbmc/interval_symex_guard_two_loops
// EXPECT: ^VERIFICATION SUCCESSFUL$
// Vereda: TIMEOUT after 60 s
// MODE: FUTURE
