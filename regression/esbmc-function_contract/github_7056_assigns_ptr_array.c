/* An element of an array *of pointers* is pointer-typed, so it used to be
 * classed as a pointer target and the whole array was still asserted
 * unchanged -- failing even here, where the body writes only the element the
 * clause names. */
int *pa[10];

void f(int i, int *v)
{
  __ESBMC_requires(i >= 0 && i < 10);
  __ESBMC_assigns(pa[i]);
  __ESBMC_ensures(1);
  pa[i] = v;
}

int main()
{
  return 0;
}
// Imported from ESBMC regression/function_contract/github_7056_assigns_ptr_array
// Needs: --enforce-contract f
// RUN: --enforce-contract f --function f
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
