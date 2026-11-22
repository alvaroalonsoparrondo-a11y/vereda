/* Past the extent an element-wise frame can afford, the array is held as one
 * equality against its snapshot with the named index replaced by its current
 * value. That is exact, and costs the same at any extent: this verifies in
 * 0.2s, where an assertion per element took 16s at 1000 and did not finish at
 * 10000. */
int global[1000];

void f(int i, int v)
{
  __ESBMC_requires(i >= 0 && i < 1000);
  __ESBMC_assigns(global[i]);
  __ESBMC_ensures(1);
  global[i] = v; /* only touches global[i], which is in assigns */
}

int main()
{
  return 0;
}
// Imported from ESBMC regression/function_contract/github_7056_assigns_large_array
// Needs: --enforce-contract f
// RUN: --enforce-contract f --function f
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
