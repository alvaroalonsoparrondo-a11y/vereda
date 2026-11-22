int nondet_int(void);
int main(void) { int x = nondet_int(); __ESBMC_assert((x & 1) <= 1, "low bit"); return 0; }
// Imported from ESBMC regression/goto2lean/unsupported_int_mode_bitwise
// Needs: --goto2lean --ir
// RUN: --goto2lean --ir
// MODE: FUTURE
// EXPECT: ^ERROR: goto2lean: unsupported bitand under --ir \(unbounded integers\)$
