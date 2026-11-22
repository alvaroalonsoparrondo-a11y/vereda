/* Test 2: Requires violation in replace mode
 * Expected: VERIFICATION FAILED
 * The requires clause (x > 0) is violated at call site
 */
#include <assert.h>

int increment(int x)
{
  __ESBMC_requires(x > 0);
  __ESBMC_ensures(__ESBMC_return_value > x);
  return x + 1;
}

int main()
{
  int a = -5;  // VIOLATION: violates requires clause (x > 0)
  int result = increment(a);  // Call replaced with contract, requires should be asserted
  
  return 0;
}

// Imported from ESBMC regression/function_contract/replace_requires_fail
// Needs: --replace-call-with-contract *
// RUN: --replace-call-with-contract "*"
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
