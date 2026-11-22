/* The idiom's trailing 0 is a no-op, so it still folds (esbmc/esbmc#7900). */
int main()
{
  int c = nondet_int();
  (void)((c) || (__ESBMC_assert(0, "v"), 0));
  return 0;
}
// Imported from ESBMC regression/esbmc/or_assert_fold_idiom_still_folds
// Needs: --goto-functions-only
// RUN: --goto-functions-only
// MODE: FUTURE
// EXPECT: ^\s+ASSERT \(_Bool\)c // v$
// EXPECT: \A(?![\s\S]*ASSERT 0 // v)[\s\S]*\Z
