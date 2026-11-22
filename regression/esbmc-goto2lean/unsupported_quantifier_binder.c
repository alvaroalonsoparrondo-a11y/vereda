unsigned nondet_uint(void);
int main(void) {
  unsigned x = nondet_uint();
  __ESBMC_assert(__ESBMC_forall((void *)1, x == x), "q");
  return 0;
}
// Imported from ESBMC regression/goto2lean/unsupported_quantifier_binder
// Needs: --goto2lean
// RUN: --goto2lean
// MODE: FUTURE
// EXPECT: ^ERROR: goto2lean: unsupported quantifier binder constant_int$
