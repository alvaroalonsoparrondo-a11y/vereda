// #9534: under --ir an assumption against a type bound must not be folded
// away, since an integer-encoded value is not confined to its type's range.
extern unsigned long nondet_ulong(void);
extern unsigned char nondet_uchar(void);
extern int nondet_int(void);

int main(void)
{
  unsigned long u = nondet_ulong();
  __VERIFIER_assume(u <= 18446744073709551615UL);
  __VERIFIER_assert(u / 2 <= 9223372036854775807UL); // unsigned max

  unsigned long v = nondet_ulong();
  __VERIFIER_assume(v >= 0);
  __VERIFIER_assume(v <= 10);
  __VERIFIER_assert(v * v <= 100); // unsigned min

  int x = nondet_int();
  __VERIFIER_assume(x >= -2147483647 - 1);
  __VERIFIER_assert(x >= -2147483648LL); // signed min

  unsigned char c = nondet_uchar();
  __VERIFIER_assume(c >= 0);
  __VERIFIER_assume(c <= 10);
  __VERIFIER_assert(c * c <= 100); // promoted unsigned
  return 0;
}
// Imported from ESBMC regression/esbmc/github_9534_ir_type_bound
// Needs: --ir
// RUN: --ir --z3 --multi-property
// MODE: FUTURE
// EXPECT: ^ +PASSED +\[main\.assertion\.1\] +line 11 +unsigned max$
// EXPECT: ^ +PASSED +\[main\.assertion\.2\] +line 16 +unsigned min$
// EXPECT: ^ +PASSED +\[main\.assertion\.3\] +line 20 +signed min$
// EXPECT: ^ +PASSED +\[main\.assertion\.4\] +line 25 +promoted unsigned$
// EXPECT: ^VERIFICATION SUCCESSFUL$
