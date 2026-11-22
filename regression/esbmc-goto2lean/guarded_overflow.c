unsigned nondet_uint(void);
int main(void) {
  unsigned a = nondet_uint(), b = nondet_uint(), c = nondet_uint();
  unsigned r = c ? a + b : 0;
  _Bool t = c && a + b > 3;
  return 0;
}
// Imported from ESBMC regression/goto2lean/guarded_overflow
// Needs: --goto2lean --unsigned-overflow-check
// RUN: --goto2lean --unsigned-overflow-check
// MODE: FUTURE
// EXPECT: ^  \(\(c ≠ 0#32\) → ¬\(\(BitVec\.uaddOverflow a b\) = true\)\) ∧ \($
// EXPECT: ^  let r := \(if \(c != 0#32\) then \(a \+ b\) else \(0#32\)\);$
