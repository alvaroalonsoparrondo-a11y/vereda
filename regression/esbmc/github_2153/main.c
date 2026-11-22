int some_var;

int main()
{
  void *bar;
  char *ptr = &bar;
  ptr[0] = nondet_char();

  __ESBMC_assert(bar != &some_var, "");
}
// Imported from ESBMC regression/esbmc/github_2153
// RUN: --incremental-bmc
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^VERIFICATION FAILED$
// MODE: FUTURE
