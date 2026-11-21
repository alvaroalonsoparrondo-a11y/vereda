// Two translation units linked with llvm-link. The call into the second one
// needs the walker to enter defined functions, which it cannot yet.
// MODE: FUTURE
// FILES: helper.c
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern void __VERIFIER_assert(int);
int helper(int x);

int main(void) {
  __VERIFIER_assert(helper(2) == 4);
  return 0;
}
