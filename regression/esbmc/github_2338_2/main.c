#include <assert.h>

int main() {
  unsigned int a = 0xFFFFFFFF;
  unsigned int result = -a;
  return result;
}

// Imported from ESBMC regression/esbmc/github_2338_2
// Needs: --unsigned-overflow-check
// RUN: --unsigned-overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
