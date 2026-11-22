int nondet_int();

int main()
{
  int x = nondet_int();
  __ESBMC_assert(x != 1, "first");
  __ESBMC_assert(x != 2, "second");
  return 0;
}
// Imported from ESBMC regression/esbmc/multi_property_kstep_single_verdict_fail
// RUN: --incremental-bmc --multi-property --max-k-step 5
// EXPECT: ^\*\* 2 of 2 properties failed$
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: \A(?![\s\S]*VERIFICATION FAILED[\s\S]*VERIFICATION FAILED)[\s\S]*\Z
// Vereda: unmet EXPECT: ^\*\* 2 of 2 properties failed$
// MODE: FUTURE
