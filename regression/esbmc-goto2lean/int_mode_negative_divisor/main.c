int __VERIFIER_nondet_int(void);
int main() {
  int a = __VERIFIER_nondet_int();
  int q = a / -2, r = a % -2;
  __ESBMC_assert(q * -2 + r == a, "identity");
  __ESBMC_assert(a >= 0 || r <= 0, "rem sign");
  __ESBMC_assert(q == -(a / 2), "neg divisor");
  return 0;
}
// Imported from ESBMC regression/goto2lean/int_mode_negative_divisor
// Needs: --goto2lean --ir
// RUN: --goto2lean --ir
// MODE: FUTURE
// EXPECT: ^  let q := \(Int\.tdiv a \(-\(2 : Int\)\)\);$
// EXPECT: ^    show Int\.sign \(-2 : Int\) = -1 from rfl,$
