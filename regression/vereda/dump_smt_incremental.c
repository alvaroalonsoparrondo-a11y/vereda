// --dump-smt prints one bound, so it does not go with --incremental-bmc.
// RUN: --dump-smt --incremental-bmc
// EXPECT: --dump-smt prints one bound; use --unwind
// EXPECT-NOT: VERIFICATION
int main(void) { return 0; }
