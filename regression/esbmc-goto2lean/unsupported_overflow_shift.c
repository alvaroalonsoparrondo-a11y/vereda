int nondet_int(void);
int main(void) {
  int x = nondet_int();
  int z = x << 1;
  return 0;
}
// Imported from ESBMC regression/goto2lean/unsupported_overflow_shift
// Needs: --goto2lean --overflow-check
// RUN: --goto2lean --overflow-check
// MODE: FUTURE
// EXPECT: ^ERROR: goto2lean: unsupported overflow check on shl$
