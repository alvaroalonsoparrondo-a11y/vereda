// Bytes written at constant addresses stay out of the byte array until an
// access at a nondet address needs them: merged at joins, known on one side
// only, overwritten through a nondet index, holding a pointer, and copied.
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern int __VERIFIER_nondet_int(void);
extern void __VERIFIER_assume(int);
extern void __VERIFIER_assert(int);
void *memcpy(void *, const void *, unsigned long);

int g = 1;
extern int ext; // no initialiser: its bytes start unknown
int a[4];
int x;
int *p = &x;

int main(void) {
  int c = __VERIFIER_nondet_int();
  int before = ext;
  if (c) {
    g = 2;
    ext = 5;
  }
  __VERIFIER_assert(g == (c ? 2 : 1));
  __VERIFIER_assert(ext == (c ? 5 : before));
  a[1] = 7;
  a[2] = 9;
  int i = __VERIFIER_nondet_int();
  __VERIFIER_assume(i >= 0 && i < 4);
  a[i] = 3;
  __VERIFIER_assert(a[1] == (i == 1 ? 3 : 7) && a[i] == 3);
  int *q = p;
  int **pp = &p;
  **pp = 4;
  __VERIFIER_assert(x == 4 && *q == 4);
  int b[4];
  memcpy(b, a, sizeof a);
  __VERIFIER_assert(b[2] == (i == 2 ? 3 : 9));
  return 0;
}
