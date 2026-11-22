#include <assert.h>

int main() {
  unsigned int a = 0x40000000;
  unsigned int result = -a;
  return result;
}
// Imported from ESBMC regression/esbmc/github_2338_6
// Needs: --unsigned-overflow-check
// RUN: --unsigned-overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
