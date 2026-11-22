int main()
{
  short a;
  int b=__VERIFIER_nondet_int();

  a = (short)b;
}
// Imported from ESBMC regression/esbmc/overflow_19_typecast
// Needs: --overflow-check
// RUN: --overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
