// /tmp/issue2.c
typedef unsigned long size_t;

__ESBMC_contract
size_t strlen(const char *s) {
    __ESBMC_requires(__ESBMC_is_fresh(s, 100));
    __ESBMC_requires(s != 0);
    __ESBMC_ensures(__ESBMC_return_value < 100);
    __ESBMC_assigns();

    size_t len = 0;
    __ESBMC_unroll(102);
    while (s[len] != 0) len++;
    return len;
}
// Imported from ESBMC regression/function_contract/github_4218
// Needs: --enforce-contract strlen --loop-invariant-check --loop-frame-rule
// RUN: --function strlen --enforce-contract strlen --loop-invariant-check --loop-frame-rule
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
