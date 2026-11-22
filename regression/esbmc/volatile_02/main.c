int main()
{
  volatile int flag = 1;

  int read = flag;

  __ESBMC_assert(read, "");
}
// Imported from ESBMC regression/esbmc/volatile_02
// Needs: --volatile-check
// RUN: --volatile-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
