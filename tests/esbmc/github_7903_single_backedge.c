int main(void) {
    unsigned r = 0;
_start:
    {
        unsigned t;
        if (r != 0) return 0;
        t = 1;
        if (__VERIFIER_nondet_int() != 0) goto after;
        r = t; goto _start;
    after:
        r = t;
        __VERIFIER_assert(r == 1); // r == 1
        return 0;
    }
}
// Imported from ESBMC regression/esbmc/github_7903_single_backedge
// RUN: --unwind 8
// EXPECT: ^VERIFICATION SUCCESSFUL$
