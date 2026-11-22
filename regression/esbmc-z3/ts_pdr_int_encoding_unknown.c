// PDR builds cubes from bit extracts, which integer encoding has no sort for.
extern unsigned char __VERIFIER_nondet_uchar(void);
extern _Bool __VERIFIER_nondet_bool(void);
extern float __VERIFIER_nondet_float(void);
extern void abort(void);
void reach_error() {}
void __VERIFIER_assert(int c) { if (!c) { ERROR: { reach_error(); abort(); } } }
int main() {
  _Bool on = __VERIFIER_nondet_bool();
  unsigned char x = 0;
  for (;;) {
    __VERIFIER_assert(on || x == 0);
    if (on)
      x = x + 1;
  }
}
// Imported from ESBMC regression/z3/ts_pdr_int_encoding_unknown
// Needs: --ir --ts-pdr
// RUN: --z3 --ir --no-pointer-check --no-bounds-check --ts-pdr --max-k-step 20
// MODE: FUTURE
// EXPECT: ^PDR: PDR needs bit-vector encoding$
// EXPECT: ^VERIFICATION UNKNOWN$
