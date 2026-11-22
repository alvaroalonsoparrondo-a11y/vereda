// #9534: the assumptions against type bounds are kept under --ir, and the
// properties below still fail because the bounds do not imply them.
extern unsigned long nondet_ulong(void);
extern unsigned char nondet_uchar(void);
extern int nondet_int(void);

int main(void)
{
  unsigned long u = nondet_ulong();
  __VERIFIER_assume(u <= 18446744073709551615UL);
  __VERIFIER_assert(u / 2 <= 4611686018427387903UL); // unsigned max

  unsigned long v = nondet_ulong();
  __VERIFIER_assume(v >= 0);
  __VERIFIER_assume(v <= 10);
  __VERIFIER_assert(v * v < 100); // unsigned min

  int x = nondet_int();
  __VERIFIER_assume(x >= -2147483647 - 1);
  __VERIFIER_assert(x > -2147483648LL); // signed min

  unsigned char c = nondet_uchar();
  __VERIFIER_assume(c >= 0);
  __VERIFIER_assume(c <= 10);
  __VERIFIER_assert(c * c < 100); // promoted unsigned
  return 0;
}
// Imported from ESBMC regression/esbmc/github_9534_ir_type_bound_fail
// Needs: --ir
// RUN: --ir --z3 --multi-property
// MODE: FUTURE
// EXPECT: ^ +FAILED +\[main\.assertion\.1\] +line 11 +unsigned max$
// EXPECT: ^ +FAILED +\[main\.assertion\.2\] +line 16 +unsigned min$
// EXPECT: ^ +FAILED +\[main\.assertion\.3\] +line 20 +signed min$
// EXPECT: ^ +FAILED +\[main\.assertion\.4\] +line 25 +promoted unsigned$
// EXPECT: ^VERIFICATION FAILED$
