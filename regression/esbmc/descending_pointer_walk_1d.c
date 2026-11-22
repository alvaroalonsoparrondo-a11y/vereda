int main()
{
  int a[5] = {1, 1, 1, 1, 1};
  int sum = 0;
  for (int *p = &a[4]; p != &a[0]; p--)
    sum += *(p - 1);
  __ESBMC_assert(sum == 4, "four elements walked backwards");
  return 0;
}
// Imported from ESBMC regression/esbmc/descending_pointer_walk_1d
// RUN: --unwind 8
// EXPECT: ^VERIFICATION SUCCESSFUL$
// EXPECT: ^Generated 9 VCC\(s\), 1 remaining after simplification
// Vereda: unmet EXPECT: ^Generated 9 VCC\(s\), 1 remaining after simplification
// MODE: FUTURE
