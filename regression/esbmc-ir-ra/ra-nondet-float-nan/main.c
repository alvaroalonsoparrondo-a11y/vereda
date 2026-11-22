extern float __VERIFIER_nondet_float(void);

int main(void)
{
  /* Single-precision nondet float also gets a NaN predicate. */
  float x = __VERIFIER_nondet_float();

  __ESBMC_assert(x == x, "unconstrained nondet float may be NaN");
  return 0;
}
// Imported from ESBMC regression/ir-ra/ra-nondet-float-nan
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
