// --max-k-step means nothing without --incremental-bmc.
// RUN: --max-k-step 3
// EXPECT: --max-k-step needs --incremental-bmc
// EXPECT-NOT: VERIFICATION
int main(void) { return 0; }
