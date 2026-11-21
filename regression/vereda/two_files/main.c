// Two translation units linked with llvm-link. The call into the second one
// needs the walker to enter defined functions, which it cannot yet.
// MODE: FUTURE
// FILES: helper.c
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern void reach_error(void);
int helper(int x);

int main(void) {
  if (helper(2) != 4)
    reach_error();
  return 0;
}
