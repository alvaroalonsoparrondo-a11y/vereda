int main(void) {
    unsigned r = 0;
_start:
    {
        unsigned t = r + 5;
        if (r != 0) { __VERIFIER_assert(r == 5); return 0; } // r == 5
        if (__VERIFIER_nondet_int() != 0) { r = t; goto _start; }
        r = 15 - t; goto _start;
    }
}
// Imported from ESBMC regression/esbmc/github_7903_fail
// RUN: --unwind 8
// EXPECT: ^VERIFICATION FAILED$
