int main(void) { int a[2] = {1, 2}; int *p = a; __ESBMC_assert(p[1] == 2, "x"); return 0; }
// Imported from ESBMC regression/goto2lean/unsupported_array
// Needs: --goto2lean
// RUN: --goto2lean
// MODE: FUTURE
// EXPECT: ^ERROR: goto2lean: unsupported type array$
