// clrsb(-2) is 30: of the 31 bits below the sign bit, only the first is a
// redundant copy of it. Exactly the wrong expectation of 31 must fail.
int nondet_int(void);

int main(void)
{
  int x = nondet_int();
  __ESBMC_assume(x == -2);
  __ESBMC_assert(__builtin_clrsb(x) == 30, "clrsb(-2) is 30");
  __ESBMC_assert(__builtin_clrsb(x) == 31, "clrsb(-2) == 31 is wrong");
  return 0;
}
// Imported from ESBMC regression/esbmc/builtin_clrsb_fail
// Needs: --clz-zero-check
// RUN: --clz-zero-check --multi-property
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: PASSED +\[main\.assertion\.1\] +line +9 +clrsb\(-2\) is 30$
// EXPECT: FAILED +\[main\.assertion\.2\] +line +10 +clrsb\(-2\) == 31 is wrong$
