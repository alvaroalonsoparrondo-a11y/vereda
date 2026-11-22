#include <assert.h>
#include <limits.h>
#include <stdint.h>

int main() {
    // Signed integer overflow
    int s_x = INT_MAX;
    s_x += 1; // this leads to UB
    return 0;
}

// Imported from ESBMC regression/esbmc/github_2357_4
// Needs: --overflow-check --ir
// RUN: --overflow-check --no-simplify --z3 --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
