/* Test: assigns compliance with empty assigns (pure function)
 * Function pure_read has an empty assigns clause — it must not modify anything.
 */

int g = 10;

int pure_read(void)
{
    __ESBMC_assigns();
    __ESBMC_ensures(__ESBMC_return_value == g);

    return g;
}
// Imported from ESBMC regression/function_contract/assigns_compliance_empty
// Needs: --enforce-contract pure_read
// RUN: --enforce-contract pure_read --function pure_read
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
