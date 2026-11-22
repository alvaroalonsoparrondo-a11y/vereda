/* github #7929: same root cause reached through arithmetic -- INT_MIN read as
 * 2147483648 makes the remainder fold to a value outside the type. */
int nondet_int(void);

int main(void)
{
  int x = nondet_int();
  int y = nondet_int();
  __ESBMC_assume(x == -2147483647 - 1);
  __ESBMC_assume(y == -104635056);
  int r = x % y;
  __ESBMC_assert(r == 9, "cex");
  return 0;
}
// Imported from ESBMC regression/smtlib/github_7929_rem
// Needs: --smtlib --smtlib-solver-prog z3 -in REQUIRES z3_binary
// RUN: --smtlib --smtlib-solver-prog "z3 -in"
// MODE: FUTURE
// EXPECT: ^  r = -54782528 \(11111100 10111100 00010101 11000000\)$
// EXPECT: ^VERIFICATION FAILED$
