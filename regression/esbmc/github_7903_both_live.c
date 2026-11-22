int main(void) {
    unsigned r = 0;
_start:
    {
        unsigned t;
        if (r >= 2) { __VERIFIER_assert(r == 2); return 0; } // r == 2
        t = r + 1;
        if (__VERIFIER_nondet_int() != 0) { r = t; goto _start; }
        r = t; goto _start;
    }
}
// Imported from ESBMC regression/esbmc/github_7903_both_live
// RUN: --unwind 8
// EXPECT: ^VERIFICATION SUCCESSFUL$
