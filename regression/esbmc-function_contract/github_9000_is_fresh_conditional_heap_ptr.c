/* #9000: a pointer that may be &s or a successful malloc satisfies is_fresh
 * when both objects are large enough. */
#include <stdlib.h>
_Bool nondet_bool();
struct P
{
  int a;
  int b;
};
void g(struct P *d)
{
  __ESBMC_requires(__ESBMC_is_fresh(d, sizeof(struct P)));
  __ESBMC_ensures(1);
  d->b = 1;
}
int main()
{
  struct P s;
  struct P *d = nondet_bool() ? &s : malloc(sizeof(struct P));
  g(d);
  return 0;
}
// Imported from ESBMC regression/function_contract/github_9000_is_fresh_conditional_heap_ptr
// Needs: --replace-call-with-contract g
// RUN: --replace-call-with-contract g --multi-property --force-malloc-success
// MODE: FUTURE
// EXPECT: ^ +PASSED.*contract requires$
// EXPECT: ^VERIFICATION SUCCESSFUL$
