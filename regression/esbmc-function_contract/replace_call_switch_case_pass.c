/* replace_call_switch_case_pass (issue #6364):
 * A contracted call at a switch-case entry is also a jump target (the switch
 * dispatch jumps to each case label). Its replacement must not be dropped, so
 * g is set in every reached case. Distinct jump-target origin from the
 * else-branch case; verified to be spuriously FAILED before the fix.
 *
 * Expected: VERIFICATION SUCCESSFUL
 */
int g = 0;

void setg(int v)
{
  __ESBMC_assigns(g);
  __ESBMC_ensures(g == v);
  g = v;
}

int main(void)
{
  int c;
  __VERIFIER_assume(c == 0 || c == 1);
  switch (c)
  {
  case 0:
    setg(5);
    break;
  case 1:
    setg(5);
    break;
  }
  __VERIFIER_assert(g == 5); // g is set by the contract in every reached case
  return 0;
}
// Imported from ESBMC regression/function_contract/replace_call_switch_case_pass
// Needs: --replace-call-with-contract *
// RUN: --replace-call-with-contract *
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
