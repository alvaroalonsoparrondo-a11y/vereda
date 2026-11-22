#include <assert.h>

int main() {
  unsigned int a = 0x80000001;
  unsigned int result = -a;
  return result;
}
// Imported from ESBMC regression/esbmc/github_2338_7
// Needs: --unsigned-overflow-check
// RUN: --unsigned-overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
