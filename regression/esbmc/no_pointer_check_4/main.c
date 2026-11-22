// Check if comparation is nondet
int main(void) {
  int p; // unique stack addr
  int q; // unique stack addr;

  __ESBMC_assume(&p < &q);
  if(&p > &q) __ESBMC_assert(0,"p shouldn't be greater than q");
  return 0;
}
// Imported from ESBMC regression/esbmc/no_pointer_check_4
// EXPECT: ^VERIFICATION SUCCESSFUL$
