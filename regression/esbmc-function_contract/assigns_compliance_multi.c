/* Test: assigns compliance with multiple targets
 * Function update modifies 'a' and 'b' which are in assigns clause.
 * Global 'c' is not in assigns and must remain unchanged.
 */

int a = 0;
int b = 0;
int c = 0;

void update(void)
{
    __ESBMC_assigns(a, b);
    __ESBMC_ensures(a == 1);
    __ESBMC_ensures(b == 2);

    a = 1;
    b = 2;
    // c must remain unchanged
}
// Imported from ESBMC regression/function_contract/assigns_compliance_multi
// Needs: --enforce-contract update
// RUN: --enforce-contract update --function update
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
