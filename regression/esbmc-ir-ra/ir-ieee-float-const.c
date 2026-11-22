/* Regression test for constant_floatbv encoding in int_encoding mode.
 * The constant 1.5 is exactly 3/2 in rational arithmetic.
 * Prior to the fix, fixed_point() misread the IEEE 754 bit pattern,
 * encoding 1.5 as 1072693248 (the upper 32 bits of the 64-bit pattern).
 */
#include <assert.h>

int main()
{
  double x = 1.5;
  assert(x > 1.0 && x < 2.0);
  return 0;
}
// Imported from ESBMC regression/ir-ra/ir-ieee-float-const
// Needs: --ir-ieee
// RUN: --ir-ieee --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
