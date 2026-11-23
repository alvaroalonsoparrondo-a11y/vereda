// Floating-point arithmetic, comparison and conversion on nondet values:
// conversions to integers truncate, as C does, and rounding is to nearest.
// RUN: --unwind 2
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern void __VERIFIER_assert(int);
extern void __VERIFIER_assume(int);
extern double __VERIFIER_nondet_double(void);
extern float __VERIFIER_nondet_float(void);
extern int __VERIFIER_nondet_int(void);
int main(void) {
  double a = __VERIFIER_nondet_double();
  __VERIFIER_assume(a > 2.5 && a < 2.75);
  __VERIFIER_assert((int)a == 2);
  __VERIFIER_assert((int)-a == -2);
  __VERIFIER_assert(a * 2 > 5.0 && a - 2 < 1);
  float f = __VERIFIER_nondet_float();
  __VERIFIER_assume(f == 0.1f);
  __VERIFIER_assert((double)f != 0.1); // 0.1f widened is not the double 0.1
  __VERIFIER_assert((float)(double)f == f);
  int i = __VERIFIER_nondet_int();
  __VERIFIER_assume(i > -1000 && i < 1000);
  __VERIFIER_assert((int)(double)i == i);
  __VERIFIER_assert((float)i / 4 * 4 == (float)i);
  return 0;
}
