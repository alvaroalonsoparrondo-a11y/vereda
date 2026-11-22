int main()
{
  volatile int flag = 0;

  while (flag != 0)
  {
    __ESBMC_assert(0, "");
  }
}
// Imported from ESBMC regression/esbmc/volatile_01
// Needs: --volatile-check
// RUN: --volatile-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
