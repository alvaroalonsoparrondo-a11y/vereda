int roundInt(double a) {
  if (a>=0)
    return (int)(a+0.5);
  else
    return (int)(a-0.5);
}

void main() {
  double a = -0.6;
  assert(roundInt(a) == -1);
}

// Imported from ESBMC regression/cbmc/01_cbmc_Fixedbv22
// Needs: --fixedbv --ir
// RUN: --fixedbv --no-slice --z3 --ir --no-simplify -Wno-error=implicit-function-declaration
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
