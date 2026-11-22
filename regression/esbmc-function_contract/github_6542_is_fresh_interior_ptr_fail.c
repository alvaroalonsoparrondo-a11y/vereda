/* github_6542_is_fresh_interior_ptr_fail:
 * An interior pointer has a non-zero offset, so the room left in the object is
 * what follows it, not the whole allocation. Dropping the offset term would
 * accept &a[3] against an extent that only the base could satisfy. */
#include <stdlib.h>

void callee(unsigned char *b) {
  __ESBMC_requires(__ESBMC_is_fresh(b, 8));
  __ESBMC_assigns(b[0]);
  __ESBMC_ensures(b[0] == 1);
  b[0] = 1;
}

int main(void) {
  unsigned char *p = (unsigned char *)malloc(10);
  __VERIFIER_assume(p != 0);
  callee(&p[3]);
  return 0;
}
// Imported from ESBMC regression/function_contract/github_6542_is_fresh_interior_ptr_fail
// Needs: --replace-call-with-contract callee
// RUN: --replace-call-with-contract callee --unwind 8
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^.*contract requires.*$
