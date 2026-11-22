/* Test: Contract annotation with replace mode
 * 
 * This test verifies that replace-call-with-contract works with annotation.
 */

int counter = 0;

__ESBMC_contract
int increment(int x)
{
    __ESBMC_requires(x >= 0);
    __ESBMC_ensures(__ESBMC_return_value == x + 1);
    __ESBMC_assigns(counter);
    
    counter++;
    return x + 1;
}

int main(void)
{
    int a = 5;
    int b = increment(a);  // This call will be replaced with contract
    __VERIFIER_assert(b == 6); // b should be 6
    return 0;
}
// Imported from ESBMC regression/function_contract/annotate_contract_replace_pass
// Needs: --replace-all-contracts
// RUN: --replace-all-contracts
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
