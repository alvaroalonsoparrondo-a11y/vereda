#include <assert.h>
#include <limits.h>
#include <stdint.h>

int main() {
    unsigned int u_x = UINT_MAX;
    u_x += 1;
    assert(u_x == 0);
    return 0;
}


// Imported from ESBMC regression/esbmc/github_2357_3
// Needs: --unsigned-overflow-check --ir
// RUN: --z3 --unsigned-overflow-check --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
