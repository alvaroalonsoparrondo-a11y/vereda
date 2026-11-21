// RUN: --dump-ir
// EXPECT: phi i32
// EXPECT-NOT: mustprogress|nsw|nuw|inbounds|optnone|noundef
// A loop with a non-constant condition and no side effects: C11 6.8.5p6 lets
// the compiler assume it terminates. The IR must keep it, with no
// mustprogress, nsw or inbounds anywhere.
extern unsigned nondet(void);
int main(void) {
  unsigned n = nondet();
  int a[4] = {0};
  int s = 0;
  for (unsigned i = 0; i < n; i++)
    s += a[i & 3] + (int)i;
  return s;
}
