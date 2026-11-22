// Ordered comparison of pointers into one object compares addresses.
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern void __VERIFIER_assert(int);

int main(void) {
  int a[4];
  int *lo = &a[0], *hi = &a[3];
  __VERIFIER_assert(lo < hi && hi - lo == 3 && lo != hi);
  return 0;
}
