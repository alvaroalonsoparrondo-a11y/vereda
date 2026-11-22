/* __ESBMC_is_fresh on a global pointer. The #7356 havoc runs before the
 * is_fresh allocation so it cannot overwrite the pointer that allocation
 * produces. Measured: this reports an invalid dereference both before that
 * change and with the havoc placed after the allocation.
 */
int *gp;

void f(void)
{
  __ESBMC_requires(__ESBMC_is_fresh(gp, sizeof(int)));
  __ESBMC_assigns(*gp);
  *gp = 1;
}

int main(void)
{
  return 0;
}
// Imported from ESBMC regression/function_contract/github_7356_is_fresh_global
// Needs: --enforce-contract f
// RUN: --enforce-contract f --function f
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
