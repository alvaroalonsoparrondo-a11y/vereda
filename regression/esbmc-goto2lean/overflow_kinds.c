int nondet_int(void);
unsigned nondet_uint(void);
int main(void) {
  int x = nondet_int(), y = nondet_int();
  unsigned a = nondet_uint(), b = nondet_uint();
  int s = x - y;
  int p = x * y;
  int q = x / y;
  int r = x % y;
  int n = -x;
  unsigned us = a - b;
  unsigned um = a * b;
  unsigned un = -a;
  return 0;
}
// Imported from ESBMC regression/goto2lean/overflow_kinds
// Needs: --goto2lean --overflow-check --unsigned-overflow-check
// RUN: --goto2lean --overflow-check --unsigned-overflow-check --no-div-by-zero-check
// MODE: FUTURE
// EXPECT: ^  ¬\(\(BitVec\.ssubOverflow x y\) = true\) ∧ \($
// EXPECT: ^  ¬\(\(BitVec\.smulOverflow x y\) = true\) ∧ \($
// EXPECT: ^  -- arithmetic overflow on div$
// EXPECT: ^  -- arithmetic overflow on modulus$
// EXPECT: ^  ¬\(\(BitVec\.sdivOverflow x y\) = true\) ∧ \($
// EXPECT: ^  ¬\(\(x == BitVec\.intMin 32\) = true\) ∧ \($
// EXPECT: ^  ¬\(\(BitVec\.usubOverflow a b\) = true\) ∧ \($
// EXPECT: ^  ¬\(\(BitVec\.umulOverflow a b\) = true\) ∧ \($
// EXPECT: ^  ¬\(\(a != 0#32\) = true\) ∧ \($
