int main(void)
{
  unsigned char c = 256;
  __VERIFIER_assert(c == 256); // no wraparound under --ir
  return 0;
}
// Imported from ESBMC regression/goto2lean/int_mode_constant_fold
// Needs: --goto2lean --ir
// RUN: --goto2lean --ir
// MODE: FUTURE
// EXPECT: ^  let c := \(256 : Int\);$
// EXPECT: ^  \(c = \(256 : Int\)\) ∧ \($
