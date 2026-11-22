int main()
{
  int x = __VERIFIER_nondet_int();
  __ESBMC_assume(x > 0);
  __ESBMC_assert(x > 0, "x stays positive");
  return 0;
}
// Imported from ESBMC regression/esbmc/segfault_handler_flag
// Needs: --segfault-handler
// RUN: --segfault-handler
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
