unsigned nondet_uint(void);
int main(void) {
  unsigned x = nondet_uint(), y = nondet_uint();
  __VERIFIER_assume(y == 0 && x == 7);
  unsigned q = x / y;
  __VERIFIER_assert(q == 0); // q
  return 0;
}
// Imported from ESBMC regression/goto2lean/div_by_zero_semantics
// Needs: --goto2lean
// RUN: --goto2lean --no-div-by-zero-check
// MODE: FUTURE
// EXPECT: ^  let q := \(BitVec\.smtUDiv x y\);$
