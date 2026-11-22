int main() {
  unsigned int a = 0;
  return -a;
}
// Imported from ESBMC regression/esbmc/github_2338_3
// Needs: --unsigned-overflow-check
// RUN: --unsigned-overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
