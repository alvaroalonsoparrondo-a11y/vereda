int main(void) {
  unsigned int i = 101;
  unsigned int j = 100;
  unsigned k = (int) i % (int) j;
  return 0;
}

// Imported from ESBMC regression/esbmc/math_mod01
// Needs: --ub-shift-check
// RUN: --no-bounds-check --no-pointer-check --no-div-by-zero-check --ub-shift-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
