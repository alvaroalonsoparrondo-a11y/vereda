/* #9000: naming a pointer field does not permit writing through it. */
struct C { int *p; int k; };
int g;
void f(struct C *c) { __ESBMC_assigns(c->p); *c->p = 5; }
int main() { struct C c; c.p = &g; c.k = 0; f(&c); return 0; }
// Imported from ESBMC regression/function_contract/github_9000_assigns_ptr_field_pointee_fail
// Needs: --enforce-contract f
// RUN: --enforce-contract f
// MODE: FUTURE
// EXPECT: ^  assigns compliance: c:@g not in assigns clause$
// EXPECT: ^VERIFICATION FAILED$
