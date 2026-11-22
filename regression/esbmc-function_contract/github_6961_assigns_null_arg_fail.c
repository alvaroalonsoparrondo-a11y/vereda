/* The havoc writes through the pointer the contract says the callee assigns,
 * so a caller passing null is reported where the removed body would have
 * faulted. This is what the no-assigns pointer havoc (section 2.4) has always
 * done; the two paths now share one skip predicate and agree here. A contract
 * that means to accept null has to say `requires(p != 0)`. */
void clr(int *p)
{
  __ESBMC_assigns(p);
  __ESBMC_ensures(1);

  p[0] = 0;
}

int main(void)
{
  int *q = 0;
  clr(q);
  return 0;
}
// Imported from ESBMC regression/function_contract/github_6961_assigns_null_arg_fail
// Needs: --replace-call-with-contract clr
// RUN: --replace-call-with-contract clr --unwind 10
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^.*dereference failure: NULL pointer.*$
