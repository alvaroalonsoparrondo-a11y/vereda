#include <assert.h>
#include <stdbool.h>

int main() {
    bool x = false;  // Equivalent to 0
    int result = -x; // Should be 0
    assert(!x);
    return 0;
}

// Imported from ESBMC regression/esbmc/github_2337_4
// Needs: --overflow-check
// RUN: --overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
