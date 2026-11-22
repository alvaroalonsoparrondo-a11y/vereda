/* Sparing the named element must not spare the array. The precondition keeps i
 * away from 0, so global[0] is an element the clause does not name. */
int global[10];

void f(int i, int v)
{
  __ESBMC_requires(i >= 1 && i < 10);
  __ESBMC_assigns(global[i]);
  __ESBMC_ensures(1);
  global[i] = v;
  global[0] = 99; /* not in __ESBMC_assigns */
}

int main()
{
  return 0;
}
// Imported from ESBMC regression/function_contract/github_7056_assigns_global_other_elem_fail
// Needs: --enforce-contract f
// RUN: --enforce-contract f --function f
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^.*global\[0\] not in assigns clause.*$
