unsigned g;
int main(void) { g = 1; __ESBMC_assert(g == 1, "g"); return 0; }
// Imported from ESBMC regression/goto2lean/unsupported_global_variable
// Needs: --goto2lean
// RUN: --goto2lean
// MODE: FUTURE
// EXPECT: ^ERROR: goto2lean: unsupported global variable c:@g at .*unsupported_global_variable\.c:1$
