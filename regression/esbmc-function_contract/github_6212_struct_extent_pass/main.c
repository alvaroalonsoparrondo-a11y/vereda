/* github_6212_struct_extent_pass:
 *   Companion to github_6212_struct_extent_fail: stating the extent with
 *   __ESBMC_is_fresh justifies s->x.
 */
typedef struct
{
  int x;
} S;

void f(S *s)
{
  __ESBMC_requires(__ESBMC_is_fresh(s, sizeof(S)));
  __ESBMC_ensures(s->x == 1);
  s->x = 1;
}

int main()
{
  return 0;
}
// Imported from ESBMC regression/function_contract/github_6212_struct_extent_pass
// Needs: --enforce-contract f
// RUN: --function f --enforce-contract f
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
