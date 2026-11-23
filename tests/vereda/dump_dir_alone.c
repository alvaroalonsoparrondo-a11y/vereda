// --dump-dir says where dumps go, not what to dump.
// RUN: --dump-dir out
// EXPECT: --dump-dir needs a --dump-\* flag
// EXPECT-NOT: VERIFICATION
int main(void) { return 0; }
