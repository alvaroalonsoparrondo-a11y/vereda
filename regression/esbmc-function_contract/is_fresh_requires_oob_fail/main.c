/* is_fresh_requires_oob_fail: __ESBMC_is_fresh(p, sizeof(int)) (canonical
 * bare-pointer form) declares a single-int allocation; reading p[100] must
 * fire the array-bounds check.
 *
 * Companion to is_fresh_requires_pass: confirms the size argument is honoured
 * end-to-end, not silently widened.
 */
__ESBMC_contract
int foo(int *p)
{
    __ESBMC_requires(__ESBMC_is_fresh(p, sizeof(int)));
    __ESBMC_ensures(1);

    return p[100];
}

int main(void) { return 0; }
// Imported from ESBMC regression/function_contract/is_fresh_requires_oob_fail
// Needs: --enforce-contract foo
// RUN: --function foo --enforce-contract foo
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^.*dereference failure: array bounds violated.*$
