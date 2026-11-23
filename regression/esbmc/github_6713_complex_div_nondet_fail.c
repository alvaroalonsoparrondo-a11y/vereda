/* Same shape as github_6713_complex_div_nondet, with a bound the quotient
   does not meet: the check has to be refuted, so the division is really
   encoded and not sliced away (#6713). */
float __VERIFIER_nondet_float(void);

int main(void)
{
  float x = __VERIFIER_nondet_float();
  __VERIFIER_assume(x > 2.0f && x < 100.0f);

  _Complex float a = x, b = 2.0f;
  a /= b;

  __VERIFIER_assert(__real__ a > 10.0f); // quotient is not always above ten
  return 0;
}
// Imported from ESBMC regression/esbmc/github_6713_complex_div_nondet_fail
// RUN: --incremental-bmc
// EXPECT: ^VERIFICATION FAILED$
