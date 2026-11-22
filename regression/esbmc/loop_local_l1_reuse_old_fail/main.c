int main()
{
  int *q = 0;
  for (int i = 0; i < 2; i++)
  {
    int x = i;
    if (i == 0)
      q = &__ESBMC_old(x);
    else
      return *q;
  }
  return 0;
}
// Imported from ESBMC regression/esbmc/loop_local_l1_reuse_old_fail
// RUN: --unwind 3
// EXPECT: accessed expired variable pointer `x'
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: accessed expired variable pointer `x'
// MODE: FUTURE
