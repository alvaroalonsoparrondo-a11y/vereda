int main()
{
  int x = nondet_int();
  _Bool b;

  if (x > 5)
  {
    b = nondet_bool();
    __VERIFIER_assert(x > 0); // an unrelated interval fact survives an unmodelled write
  }
  return 0;
}
// Imported from ESBMC regression/esbmc/interval_bool_assign
// Needs: --interval-analysis
// RUN: --interval-analysis
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
// EXPECT: ^Generated 1 VCC\(s\), 0 remaining after simplification
