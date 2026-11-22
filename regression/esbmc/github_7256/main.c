#include <assert.h>

int main()
{
  int x = 3;
  assert(x > 100);
  assert(x != 3);
  return 0;
}
// Imported from ESBMC regression/esbmc/github_7256
// Needs: --result-only --show-cex
// RUN: --result-only --show-cex
// MODE: FUTURE
// EXPECT: ^  FAILED +\[main\.assertion\.1\]  line 6  assertion x > 100$
// EXPECT: ^\*\* 1 of 2 properties failed, 1 not checked$
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: \A(?![\s\S]*produced no model)[\s\S]*\Z
