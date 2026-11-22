unsigned nondet_uint(void);
int main(void) {
  unsigned a = nondet_uint(), b = nondet_uint(), x = 0;
  if (a) {
    if (b) {
      x = 1;
      goto out;
    }
    x = 2;
  }
  x = 3;
out:
  __ESBMC_assert(x != 0, "x");
  return 0;
}
// Imported from ESBMC regression/goto2lean/unsupported_jump_out_of_branch
// Needs: --goto2lean
// RUN: --goto2lean
// MODE: FUTURE
// EXPECT: ^ERROR: goto2lean: unsupported unstructured jump out of a branch at .*main\.c:9$
