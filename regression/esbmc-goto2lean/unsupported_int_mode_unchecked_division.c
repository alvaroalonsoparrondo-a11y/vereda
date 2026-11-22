int __VERIFIER_nondet_int(void);
int main(void) { int x = __VERIFIER_nondet_int(), y = __VERIFIER_nondet_int(); int q = x / y; return 0; }
// Imported from ESBMC regression/goto2lean/unsupported_int_mode_unchecked_division
// Needs: --goto2lean --ir
// RUN: --goto2lean --ir --no-div-by-zero-check
// MODE: FUTURE
// EXPECT: ^ERROR: goto2lean: unsupported division by a variable under --ir with --no-div-by-zero-check
