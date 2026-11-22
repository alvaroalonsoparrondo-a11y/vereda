/* enforce_temp_write_reset_fail:
 *   Companion to enforce_temp_write_restored_pass. Resetting h to its
 *   initialiser is not a restore: the entry harness havocs globals (#7881),
 *   so h may hold any value on entry and the exit check against the entry
 *   snapshot must catch the write.
 */
int g = 0;
int h = 0;

void foo(void)
{
  __ESBMC_assigns(g);
  __ESBMC_ensures(g == 42);
  g = 42;
  h = 99;
  h = 0;
}

int main(void)
{
  foo();
  return 0;
}
// Imported from ESBMC regression/function_contract/enforce_temp_write_reset_fail
// Needs: --enforce-contract foo
// RUN: --function foo --enforce-contract foo
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^.*assigns compliance: c:@h not in assigns clause.*$
