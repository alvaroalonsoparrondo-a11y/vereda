int main() {
  unsigned int a = 0x80000000;
  return -a;
}
// Imported from ESBMC regression/esbmc/github_2338
// Needs: --unsigned-overflow-check
// RUN: --unsigned-overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
