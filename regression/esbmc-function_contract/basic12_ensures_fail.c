/* Basic12_ensures_fail: Boundary value violation
 * This should FAIL - violates ensures with boundary value
 */
#include <assert.h>

int increment(int x)
{


  __ESBMC_ensures(__ESBMC_return_value > x);

  // VIOLATION: returns same value (not greater)
  return x;  // Should be x + 1 (greater than x)
}

int main()
{



  int result = increment(5);
  return 0;
}

// Imported from ESBMC regression/function_contract/basic12_ensures_fail
// Needs: --enforce-contract *
// RUN: --enforce-contract "*"
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
