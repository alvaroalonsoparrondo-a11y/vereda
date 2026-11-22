/* Test: assigns compliance with pointer dereference + direct global — PASS
 * Function foo declares assigns(*ptr, g) and writes both g directly
 * and through *ptr. Global h is not modified, so compliance should pass.
 */

int g = 0;
int h = 0;
int x = 0;

void foo(int *ptr)
{
    __ESBMC_assigns(*ptr, g);
    __ESBMC_ensures(g == 10);

    g = 10;
    *ptr = 42;
    // h and x are NOT modified — compliance should pass
}

int main()
{
    foo(&x);
    return 0;
}
// Imported from ESBMC regression/function_contract/assigns_compliance_ptr_alias_pass
// Needs: --enforce-contract foo
// RUN: --enforce-contract foo
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
