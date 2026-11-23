// An uninitialised local may hold any value, not one the compiler picks.
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: line 8
extern void __VERIFIER_assert(int);
int main(void) {
  int x;
  int y = x;
  __VERIFIER_assert(y == 0);
  return 0;
}
