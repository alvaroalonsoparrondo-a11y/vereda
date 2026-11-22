int main()
{
L:
  int a = 1, b = 2;
  int *p = &b;
  __ESBMC_assert(*p == 1, "b holds 2, not 1");
  return a;
}
// Imported from ESBMC regression/esbmc/label_multi_decl_scope_fail
// EXPECT: b holds 2, not 1
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^VERIFICATION FAILED$
// MODE: FUTURE
