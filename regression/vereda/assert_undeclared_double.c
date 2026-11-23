// An undeclared assert gets its argument unconverted: a double is true when
// nonzero, NaN included, as C reads any scalar.
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: line 12
extern double __VERIFIER_nondet_double(void);
int main(void) {
  double x = __VERIFIER_nondet_double();
  assert(1.5);
  assert(0.0 / 0.0);
  if (x != x)
    assert(x);
  assert(x);
  return 0;
}
