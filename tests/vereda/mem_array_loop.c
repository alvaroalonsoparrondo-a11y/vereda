// A local array filled in a loop and read back.
// RUN: --unwind 11
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern void __VERIFIER_assert(int);

int main(void) {
  int a[10];
  for (int i = 0; i < 10; i++)
    a[i] = i * i;
  __VERIFIER_assert(a[5] == 25 && a[9] == 81);
  return 0;
}
