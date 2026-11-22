/* The store form must still catch a write outside the frame, or an array too
 * large to hold element by element would simply stop being checked. */
int global[1000];

void f(int i, int v)
{
  __ESBMC_requires(i >= 1 && i < 1000);
  __ESBMC_assigns(global[i]);
  __ESBMC_ensures(1);
  global[i] = v;
  global[0] = 99; /* not in __ESBMC_assigns */
}

int main()
{
  return 0;
}
// Imported from ESBMC regression/function_contract/github_7056_assigns_large_array_fail
// Needs: --enforce-contract f
// RUN: --enforce-contract f --function f
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^.*global not in assigns clause.*$
