// A long double (x86_fp80) is held as its bits: negation and fabsl are bit
// operations on its sign and work; arithmetic and comparisons are
// unsupported (float_long_double_cmp.c).
// RUN: -m64
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern long double fabsl(long double);
extern long double x;
long double y;
int main(void) {
  y = -x;
  y = fabsl(y);
  return 0;
}
