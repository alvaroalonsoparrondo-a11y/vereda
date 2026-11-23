// A float in memory is its bits: stored, read back through a union as an
// integer, and copied between arrays.
// RUN: --unwind 4
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern void __VERIFIER_assert(int);
extern void __VERIFIER_assume(int);
extern float __VERIFIER_nondet_float(void);
union pun { float f; unsigned u; };
static double table[3] = {0.5, -1.25, 3.0};
int main(void) {
  union pun v;
  v.f = __VERIFIER_nondet_float();
  __VERIFIER_assume(v.f == 1.0f);
  __VERIFIER_assert(v.u == 0x3f800000u);
  v.u = 0xc0000000u;
  __VERIFIER_assert(v.f == -2.0f);
  double copy[3];
  for (int i = 0; i < 3; ++i)
    copy[i] = table[i] * 2;
  __VERIFIER_assert(copy[0] == 1.0 && copy[1] == -2.5 && copy[2] == 6.0);
  return 0;
}
