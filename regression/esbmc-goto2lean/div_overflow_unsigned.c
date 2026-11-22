unsigned nondet_uint(void);
int main(void) {
  unsigned x = nondet_uint(), y = nondet_uint();
  unsigned q = x / y;
  return 0;
}
// Imported from ESBMC regression/goto2lean/div_overflow_unsigned
// Needs: --goto2lean --unsigned-overflow-check
// RUN: --goto2lean --unsigned-overflow-check --no-div-by-zero-check
// MODE: FUTURE
// EXPECT: ^  ¬\(\(y == 0#32\) = true\) ∧ \($
