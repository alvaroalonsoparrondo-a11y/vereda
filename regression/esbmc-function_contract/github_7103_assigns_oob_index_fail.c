/* An index outside the array excuses nothing. Fed straight to a store it did:
 * the solver's index domain is only as wide as the extent, so 1024 wrapped to
 * 0 and spared the very element this body writes. The element-wise path always
 * rejected this shape, so crossing the cap turned a rejection into acceptance. */
int global[1000];

void f(int v)
{
  __ESBMC_assigns(global[1024]);
  __ESBMC_ensures(1);
  global[0] = v;
}

int main()
{
  return 0;
}
// Imported from ESBMC regression/function_contract/github_7103_assigns_oob_index_fail
// Needs: --enforce-contract f
// RUN: --enforce-contract f --function f --no-bounds-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^.*global not in assigns clause.*$
