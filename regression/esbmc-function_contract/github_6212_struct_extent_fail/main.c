/* github_6212_struct_extent_fail:
 *   The contract states only that s is non-null, so the write to s->x is not
 *   justified and must be caught. Struct parameters used to keep a
 *   one-element stack backing, which admitted it (#6212).
 */
typedef struct
{
  int x;
} S;

void f(S *s)
{
  __ESBMC_requires(s != 0);
  __ESBMC_ensures(1);
  s->x = 1;
}

int main()
{
  return 0;
}
// Imported from ESBMC regression/function_contract/github_6212_struct_extent_fail
// Needs: --enforce-contract f
// RUN: --function f --enforce-contract f
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^.*contract states no extent for pointer parameter\(s\) s.*$
