// With --fp2bv, camada's encoding keeps a NaN's payload through arithmetic
// and quiets it, as hardware does. float_nan_payload_native.c is the same
// program under the solver's theory, where the result's bits are any NaN.
// RUN: --fp2bv --unwind 2
// EXPECT: ^VERIFICATION SUCCESSFUL$
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
