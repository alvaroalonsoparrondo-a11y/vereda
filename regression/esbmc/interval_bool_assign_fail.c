_Bool flag = 0;

int main()
{
  flag = nondet_bool();
  if (!flag)
  {
    flag = 1;
    __ESBMC_assert(!flag, "stale interval fact must not survive the write");
  }
  return 0;
}
// Imported from ESBMC regression/esbmc/interval_bool_assign_fail
// Needs: --interval-analysis
// RUN: --interval-analysis
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
