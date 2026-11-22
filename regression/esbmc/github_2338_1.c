#include <assert.h>

int main() {
  unsigned int a = 0;
  unsigned int result = -a; // Should remain 0 (no overflow)
  assert(!result);
  return result;
}

// Imported from ESBMC regression/esbmc/github_2338_1
// Needs: --unsigned-overflow-check
// RUN: --unsigned-overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
