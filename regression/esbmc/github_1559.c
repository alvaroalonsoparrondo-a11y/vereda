int main()
{
  unsigned int x = 0;
  unsigned int y = 2;
  unsigned int z = y - x;
}
// Imported from ESBMC regression/esbmc/github_1559
// Needs: --unsigned-overflow-check
// RUN: --unsigned-overflow-check --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
