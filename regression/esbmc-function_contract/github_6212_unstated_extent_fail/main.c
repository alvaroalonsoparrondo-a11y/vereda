/* github_6212_unstated_extent_fail:
 * The contract states only that p is non-null, which says nothing about how
 * many elements p addresses. The harness must therefore leave p's extent
 * unconstrained, so the write to p[20] is not justified and must be caught.
 *
 * Before the fix the harness backed p with a fixed 100-byte object, so every
 * index below 25 was silently accepted and this reported SUCCESSFUL.
 */
void f(int *p)
{
  __ESBMC_requires(p != 0);
  __ESBMC_ensures(1);
  p[20] = 1;
}

int main()
{
  return 0;
}
// Imported from ESBMC regression/function_contract/github_6212_unstated_extent_fail
// Needs: --enforce-contract f
// RUN: --function f --enforce-contract f
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^.*dereference failure: array bounds violated.*$
// EXPECT: ^.*contract states no extent for pointer parameter\(s\) p.*$
