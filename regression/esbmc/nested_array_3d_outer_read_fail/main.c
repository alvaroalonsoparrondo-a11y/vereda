int nondet_int(void);

int main(void)
{
  int a[2][2][2];
  int i = nondet_int();
  __ESBMC_assume(i >= 0 && i < 2);

  a[0][0][0] = 1; a[0][0][1] = 2; a[0][1][0] = 3; a[0][1][1] = 4;
  a[1][0][0] = 5; a[1][0][1] = 6; a[1][1][0] = 7; a[1][1][1] = 8;

  __ESBMC_assert(a[i][0][0] > 4, "the same read, asserted wrong");
  return 0;
}
// Imported from ESBMC regression/esbmc/nested_array_3d_outer_read_fail
// EXPECT: ^\s*FAILED\s+\[main\.assertion\.1\]\s+line\s+12\s+the same read, asserted wrong$
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^\s*FAILED\s+\[main\.assertion\.1\]\s+line\s+12\s+the same read, asserted wrong$
// MODE: FUTURE
