/* #9000: an assigns clause naming a pointer field covers that field. */
#include <stdlib.h>
struct C { int *p; int k; };
void f(struct C *c) { __ESBMC_assigns(c->p, c->k); c->p = malloc(4); c->k = 1; }
int main() { struct C c; c.p = 0; f(&c); return 0; }
// Imported from ESBMC regression/function_contract/github_9000_assigns_ptr_field
// Needs: --enforce-contract f
// RUN: --enforce-contract f --force-malloc-success
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
