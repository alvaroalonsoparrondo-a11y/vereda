/* Test: __ESBMC_assigns() for pure functions
 * 
 * Verifies that __ESBMC_assigns() (empty) marks a function
 * as pure, meaning it has no side effects.
 */
#include <assert.h>

int global_x = 10;
int global_y = 20;

int sum_globals() {
    __ESBMC_assigns();  // Pure function: no side effects
    __ESBMC_ensures(__ESBMC_return_value == global_x + global_y);
    return global_x + global_y;
}

int main() {
    int result = sum_globals();
    
    // Globals should be unchanged
    assert(global_x == 10);
    assert(global_y == 20);
    assert(result == 30);
    
    return 0;
}
// Imported from ESBMC regression/function_contract/assigns_empty_pure_pass
// Needs: --replace-call-with-contract sum_globals
// RUN: --replace-call-with-contract "sum_globals"
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
