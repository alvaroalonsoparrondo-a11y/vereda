#include <assert.h>
#include <limits.h>
#include <stdint.h>

int main() {
    // Typecasting signed negative to unsigned
    int negative_value = -1;
    unsigned int casted_unsigned = (unsigned int) negative_value;
    // Under --ir integers are unbounded, so the cast does not wrap (#10537).
    assert(casted_unsigned == UINT_MAX);
    return 0;
}

// Imported from ESBMC regression/esbmc/github_2357_5
// Needs: --overflow-check --unsigned-overflow-check --ir
// RUN: --overflow-check --unsigned-overflow-check  --z3 --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: assertion casted_unsigned == UINT_MAX
