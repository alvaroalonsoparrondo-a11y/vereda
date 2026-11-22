/* #9000: a pointer that may be &s or NULL, then assumed non-NULL, still
 * satisfies is_fresh for the size of s. */
_Bool nondet_bool();
struct P
{
  int a;
};
void g(struct P *d)
{
  __ESBMC_requires(__ESBMC_is_fresh(d, sizeof(struct P)));
  __ESBMC_ensures(1);
  d->a = 1;
}
int main()
{
  struct P s;
  struct P *d = nondet_bool() ? &s : 0;
  __VERIFIER_assume(d != 0);
  g(d);
  return 0;
}
// Imported from ESBMC regression/function_contract/github_9000_is_fresh_conditional_ptr
// Needs: --replace-call-with-contract g
// RUN: --replace-call-with-contract g --multi-property
// MODE: FUTURE
// EXPECT: ^ +PASSED.*contract requires$
// EXPECT: ^VERIFICATION SUCCESSFUL$
