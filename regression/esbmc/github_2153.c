int some_var;

int main()
{
  void *bar;
  char *ptr = &bar;
  ptr[0] = nondet_char();

  __VERIFIER_assert(bar != &some_var);
}
// Imported from ESBMC regression/esbmc/github_2153
// RUN: --incremental-bmc
// EXPECT: ^VERIFICATION FAILED$
