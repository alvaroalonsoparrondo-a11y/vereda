int __VERIFIER_nondet_int(void);
int main(void) { int x = __VERIFIER_nondet_int(); __VERIFIER_assert((x & 1) <= 1); return 0; } // low bit
// Imported from ESBMC regression/goto2lean/unsupported_int_mode_bitwise
// Needs: --goto2lean --ir
// RUN: --goto2lean --ir
// MODE: FUTURE
// EXPECT: ^ERROR: goto2lean: unsupported bitand under --ir \(unbounded integers\)$
