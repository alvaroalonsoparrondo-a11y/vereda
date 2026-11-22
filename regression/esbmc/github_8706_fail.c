/* github #8706 */
#include <assert.h>
#include <limits.h>
unsigned nondet_uint();
int nondet_int();
int main(void)
{
  unsigned a = nondet_uint(), b = nondet_uint();
  __VERIFIER_assume(a == 0x80000000u && b == 0xffffffffu);
  unsigned q = a / b;
  assert(q == 1);
  int x = nondet_int(), y = nondet_int();
  __VERIFIER_assume(x == INT_MIN && y == -1);
  int s = x / y;
  return s;
}
// Imported from ESBMC regression/esbmc/github_8706_fail
// Needs: --overflow-check --unsigned-overflow-check
// RUN: --overflow-check --unsigned-overflow-check --bitwuzla --multi-property
// MODE: FUTURE
// EXPECT: ^  PASSED .*line +10  arithmetic overflow on div$
// EXPECT: ^  FAILED .*line +11  assertion q == 1$
// EXPECT: ^  FAILED .*line +14  arithmetic overflow on div$
// EXPECT: ^VERIFICATION FAILED$
