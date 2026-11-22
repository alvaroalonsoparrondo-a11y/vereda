/* #9000: naming *c->p permits writing through the field. */
struct C { int *p; int k; };
int g;
void f(struct C *c) { __ESBMC_assigns(*c->p); *c->p = 5; }
int main() { struct C c; c.p = &g; c.k = 0; f(&c); return 0; }
// Imported from ESBMC regression/function_contract/github_9000_assigns_ptr_field_deref
// Needs: --enforce-contract f
// RUN: --enforce-contract f
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
