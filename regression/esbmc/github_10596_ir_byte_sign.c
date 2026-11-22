// Under --ir, a value rebuilt from bytes reads its bits as two's complement.
int nondet_int(void);
int main(void)
{
  int a[2];
  int *p = a;
  int i = nondet_int();
  __VERIFIER_assume(i >= 0 && i < 2);
  a[0] = -16777217;
  a[1] = -1;
  __VERIFIER_assert(p[i] < 0); // negative through pointer
  __VERIFIER_assert(((char *)a)[4] == -1); // byte as signed char
  signed char c = -1;
  __VERIFIER_assert(*(unsigned char *)&c == 255); // signed char as unsigned
  return 0;
}
// Imported from ESBMC regression/esbmc/github_10596_ir_byte_sign
// Needs: --ir
// RUN: --z3 --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
