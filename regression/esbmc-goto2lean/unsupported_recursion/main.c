unsigned f(unsigned n) { return n == 0 ? 0 : f(n - 1); }
int main(void) { __ESBMC_assert(f(3) == 0, "f"); return 0; }
// Imported from ESBMC regression/goto2lean/unsupported_recursion
// Needs: --goto2lean
// RUN: --goto2lean
// MODE: FUTURE
// EXPECT: ^ERROR: goto2lean: unsupported recursive function f$
