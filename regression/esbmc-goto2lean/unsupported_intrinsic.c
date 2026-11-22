unsigned nondet_uint(void);
int main(void) {
  unsigned x = nondet_uint();
  if (x == 3) reach_error();
  return 0;
}
// Imported from ESBMC regression/goto2lean/unsupported_intrinsic
// Needs: --goto2lean
// RUN: --goto2lean
// MODE: FUTURE
// EXPECT: ^ERROR: goto2lean: unsupported call to intrinsic __ESBMC_unreachable
