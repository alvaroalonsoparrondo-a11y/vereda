// --incremental-bmc solves each bound to pick the next, so --dump-smt-only
// does not go with it.
// RUN: --dump-smt-only --incremental-bmc
// EXPECT: --dump-smt-only stops before the solver picks the bound; use --unwind
// EXPECT-NOT: VERIFICATION
int main(void) { return 0; }
