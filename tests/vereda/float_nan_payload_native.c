// Under the solver's floating-point theory (the default) a NaN result is a
// NaN, but its bits are not fixed: the payload check fails. With --fp2bv
// the same program passes (float_nan_payload.c).
// RUN: --unwind 2
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^  FAILED +\[main\.assertion\.2\]  line 19 
extern void __VERIFIER_assert(int);
extern void __VERIFIER_assume(int);
extern float __VERIFIER_nondet_float(void);
extern unsigned __VERIFIER_nondet_uint(void);
union pun { float f; unsigned u; };
int main(void) {
  float one = __VERIFIER_nondet_float();
  __VERIFIER_assume(one == 1.0f);
  union pun x = {.u = __VERIFIER_nondet_uint()}, y; // nondet, or InstCombine folds
  __VERIFIER_assume(x.u == 0x7f800001u);           // a signalling NaN, payload 1
  y.f = x.f * one;
  __VERIFIER_assert(y.f != y.f);
  __VERIFIER_assert(y.u == 0x7fc00001u);
  return 0;
}
