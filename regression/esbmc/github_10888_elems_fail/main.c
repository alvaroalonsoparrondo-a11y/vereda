/* #10888: the second member comes from the next element. */
#include <assert.h>
struct U
{
  unsigned char f1, f2;
};
struct G
{
  struct U f1, f2;
};
unsigned char nondet_uchar(void);
int main(void)
{
  struct U arr[3] = {
    {nondet_uchar(), nondet_uchar()},
    {nondet_uchar(), nondet_uchar()},
    {nondet_uchar(), nondet_uchar()}};
  struct G g = *(struct G *)&arr[1];
  assert(g.f2.f1 == arr[1].f1);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_10888_elems_fail
// RUN: --multi-property
// EXPECT: ^  FAILED .* assertion g.f2.f1 == arr\[1\].f1$
// EXPECT: ^\*\* 1 of 2 properties failed, 1 passed$
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^  FAILED .* assertion g.f2.f1 == arr\[1\].f1$
// MODE: FUTURE
