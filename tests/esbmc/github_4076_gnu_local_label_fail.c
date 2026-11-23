// Negative counterpart of github_4076_gnu_local_label: the loop through the
// local label really does run, so a claim that it does not is refuted rather
// than vacuously held (issue #4076).
int main(void)
{
  int x = 1;

  ({
    __label__ mylabel;
  mylabel:
    x++;
    if (x != 3)
      goto mylabel;
  });

  __VERIFIER_assert(x == 2); // must not hold
  return 0;
}
// Imported from ESBMC regression/esbmc/github_4076_gnu_local_label_fail
// RUN: --unwind 5
// EXPECT: ^VERIFICATION FAILED$
