/* replace_call_branch_target_fail (issue #6364):
 * Negative counterpart: force the else path and assert the negation of fb's
 * postcondition. With the branch-target replacement correctly applied, fb's
 * contract sets b_done == 1, so asserting !b_done must fail (rather than being
 * spuriously provable because the replacement was dropped).
 *
 * Expected: VERIFICATION FAILED
 */
typedef struct
{
  int received;
} T;
_Bool b_done = 0;

void fb(T *self, int v)
{
  __ESBMC_requires(self != 0);
  __ESBMC_assigns(self->received, b_done);
  __ESBMC_ensures(self->received == v);
  __ESBMC_ensures(b_done == 1);
  self->received = v;
  b_done = 1;
}

int main(void)
{
  T t2;
  int c;
  __VERIFIER_assume(c == 1);
  if (c == 0)
  {
    fb(&t2, 2);
  }
  else
  {
    fb(&t2, 2);
  }
  __VERIFIER_assert(!b_done); // b_done is set by fb's contract, so this must fail
  return 0;
}
// Imported from ESBMC regression/function_contract/replace_call_branch_target_fail
// Needs: --replace-call-with-contract *
// RUN: --replace-call-with-contract *
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
