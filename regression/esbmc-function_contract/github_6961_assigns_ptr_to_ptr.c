/* `&r` names the place already, so the havoc writes to r. Following the
 * pointer as well wrote through r instead, dereferencing whatever the caller
 * happened to hold -- here a null pointer, reported at the call site. */
int gv = 5;

void setp(int **pp)
{
  __ESBMC_assigns(pp);
  __ESBMC_ensures(*pp == &gv);

  *pp = &gv;
}

int main(void)
{
  int *r = 0;
  setp(&r);
  __ESBMC_assert(r == &gv, "r points at gv");
  return 0;
}
// Imported from ESBMC regression/function_contract/github_6961_assigns_ptr_to_ptr
// Needs: --replace-call-with-contract setp
// RUN: --replace-call-with-contract setp
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
