struct S { unsigned short a, b, c; };
struct S s[4];
int main(void)
{
  int j = nondet_int();
  __VERIFIER_assume(j == 0 || j == 1);
  unsigned long long *r = (unsigned long long *)s + j;
  *r = 0x0004000300020001ull;
  __VERIFIER_assert(j != 1 || s[2].a == 0); // j=1 writes s[2].a=3: expect FAIL
  return 0;
}
// Imported from ESBMC regression/esbmc/array_struct_spanning_stride_fail
// EXPECT: ^  j=1 writes s\[2\]\.a=3: expect FAIL$
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^  j=1 writes s\[2\]\.a=3: expect FAIL$
// MODE: FUTURE
