int main()
{
  char idx;
  int prop = __ESBMC_forall(&idx, idx == idx + 1);
  __ESBMC_assert(prop, "prop");
  return 0;
}
// Imported from ESBMC regression/z3/quantifiers-noncast-fail
// RUN: --solver z3 --incremental-bmc
// MODE: THOROUGH
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^VERIFICATION FAILED$
// MODE: FUTURE
