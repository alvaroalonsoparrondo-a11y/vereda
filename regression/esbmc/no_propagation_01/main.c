int main()
{
  int x = 42;
  int y = x + 1;
  __ESBMC_assert(y == 43, "y is 43");
  return 0;
}
// Imported from ESBMC regression/esbmc/no_propagation_01
// EXPECT: ^Generated 1 VCC\(s\), 0 remaining after simplification
// EXPECT: ^VERIFICATION SUCCESSFUL$
// Vereda: unmet EXPECT: ^Generated 1 VCC\(s\), 0 remaining after simplification
// MODE: FUTURE
