/* A row of a two-dimensional global is an element like any other, so the same
 * per-element assertion covers it. */
int m[3][4];

void f(int i, int v)
{
  __ESBMC_requires(i >= 0 && i < 3);
  __ESBMC_assigns(m[i]);
  __ESBMC_ensures(1);
  m[i][0] = v;
}

int main()
{
  return 0;
}
// Imported from ESBMC regression/function_contract/github_7056_assigns_global_2d
// Needs: --enforce-contract f
// RUN: --enforce-contract f --function f
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
