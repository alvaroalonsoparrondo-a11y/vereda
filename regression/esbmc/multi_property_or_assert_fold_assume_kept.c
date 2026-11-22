/* The fold dropped the assume(0) after a failed assertion (esbmc/esbmc#7900). */
int main()
{
  int c = nondet_int();
  if (!c)
  {
    __ESBMC_assert(0, "v");
    __ESBMC_assume(0);
  }
  __ESBMC_assert(c != 0, "w");
  return 0;
}
// Imported from ESBMC regression/esbmc/multi_property_or_assert_fold_assume_kept
// RUN: --multi-property
// EXPECT: ^\s+PASSED\s+\[main\.assertion\.\d+\]\s+line\s+10\s+w$
// EXPECT: ^\s+FAILED\s+\[main\.assertion\.\d+\]\s+line\s+7\s+v$
// Vereda: unmet EXPECT: ^\s+PASSED\s+\[main\.assertion\.\d+\]\s+line\s+10\s+w$
// MODE: FUTURE
