/* enforce_temp_write_restored_pass:
 *   The frame rule is observational: it compares each unlisted location at
 *   exit with its value at entry. A write to h that is undone before exit
 *   therefore complies with an assigns clause that names only g, whatever h
 *   held on entry. The entry harness havocs h, so the body must restore the
 *   value it found rather than the initialiser.
 */
int g = 0;
int h = 0;

void foo(void)
{
  __ESBMC_assigns(g);
  __ESBMC_ensures(g == 42);
  g = 42;
  int t = h;
  h = 99;
  h = t;
}

int main(void)
{
  foo();
  return 0;
}
// Imported from ESBMC regression/function_contract/enforce_temp_write_restored_pass
// Needs: --enforce-contract foo
// RUN: --function foo --enforce-contract foo
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
