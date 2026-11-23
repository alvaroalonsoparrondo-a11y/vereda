// Two translation units linked with llvm-link; the call walks into the
// second one.
// FILES: helper.c
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern void __VERIFIER_assert(int);
int helper(int x);

int main(void) {
  __VERIFIER_assert(helper(2) == 4);
  return 0;
}
