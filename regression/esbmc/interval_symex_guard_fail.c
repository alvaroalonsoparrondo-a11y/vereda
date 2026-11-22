/* The loop exits when idx == 5, so idx > 5 is false. */
int main()
{
  int idx;
  __ESBMC_assume(0 <= idx);
  while (idx < 5)
    ++idx;
  __ESBMC_assert(idx > 5, "idx should be > 5");
  return 0;
}
// Imported from ESBMC regression/esbmc/interval_symex_guard_fail
// EXPECT: ^VERIFICATION FAILED$
// Vereda: TIMEOUT after 60 s
// MODE: FUTURE
