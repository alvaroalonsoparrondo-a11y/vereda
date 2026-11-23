/* github #8659 */
int __VERIFIER_nondet_int();
int main(void)
{
  int x = __VERIFIER_nondet_int();
  int r = 0 - x;
  return r;
}
// Imported from ESBMC regression/esbmc/github_8659_fail
// Needs: --overflow-check
// RUN: --overflow-check --z3
// MODE: FUTURE
// EXPECT: ^  FAILED .*line 6  arithmetic overflow on sub$
// EXPECT: ^VERIFICATION FAILED$
