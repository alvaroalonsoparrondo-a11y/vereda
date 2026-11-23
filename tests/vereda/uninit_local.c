// An uninitialised local is one nondet value, as in ESBMC: every read of it
// agrees, for scalars, floats, pointers and the fields of a struct.
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern void __VERIFIER_assert(int);
struct pair { int a; double b; };
static int succ(int v) { return v + 1; }
int main(void) {
  int y;
  int a = y;
  __VERIFIER_assert(succ(a) == y + 1);
  double f;
  __VERIFIER_assert(f != f || f == f + 0.0);
  int *p;
  __VERIFIER_assert(p == p);
  struct pair s, q;
  s = q;
  __VERIFIER_assert(s.a == q.a);
  return 0;
}
