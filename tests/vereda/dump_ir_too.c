// --dump-ir-too prints the IR and then verifies.
// RUN: --dump-ir-too
// EXPECT: ^define dso_local i32 @main
// EXPECT: VERIFICATION SUCCESSFUL
extern void __VERIFIER_assert(int);
int main(void) {
  int x = 3;
  __VERIFIER_assert(x == 3);
  return 0;
}
