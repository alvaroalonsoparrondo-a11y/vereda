int main()
{
  int a[2][3];
  int steps = 0;
  for (int *p = &a[1][2]; p != &a[0][0]; p--)
    steps++;
  __ESBMC_assert(steps == 5, "five steps back to the first element");
  return 0;
}
// Imported from ESBMC regression/esbmc/descending_pointer_walk
// RUN: --unwind 8
// EXPECT: ^VERIFICATION SUCCESSFUL$
// EXPECT: ^Generated 1 VCC\(s\), 1 remaining after simplification
// Vereda: unmet EXPECT: ^Generated 1 VCC\(s\), 1 remaining after simplification
// MODE: FUTURE
