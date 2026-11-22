int __VERIFIER_nondet_int(void);
int main(void) {
  int x = __VERIFIER_nondet_int();
  long y = x;
  _Bool b = x;
  int z = b;
  __VERIFIER_assert(y == x && z <= 1 && x * x >= 0); // casts are identities
  return 0;
}
// Imported from ESBMC regression/goto2lean/int_mode_casts
// Needs: --goto2lean --ir
// RUN: --goto2lean --ir
// MODE: FUTURE
// EXPECT: ^  ∀ x : Int,$
// EXPECT: \(x != \(0 : Int\)\)
// EXPECT: then \(1 : Int\) else \(0 : Int\)
