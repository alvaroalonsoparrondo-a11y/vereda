/* #10089: under --ir a store at a dynamic offset spanning two struct members
 * was dropped, so the second assertion verified. */
#include <assert.h>
struct S
{
  unsigned int a;
  unsigned int b;
};
struct S s[2];
int main(void)
{
  int i = nondet_int();
  __VERIFIER_assume(i >= 0 && i < 2);
  unsigned char *p = (unsigned char *)&s[i];
  *(unsigned long long *)p = 0x0000000200000001ULL;
  assert(s[i].b == 0);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_10089_fail
// Needs: --ir
// RUN: --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^  dereference failure: Store spanning struct members under integer encoding$
