// A target of another type is called with its arguments converted, as CBMC
// does: a definition without a prototype through a typed pointer, an int
// function through a long one, and a long one through a pointer one.
// RUN: --unwind 2 -m64
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: line 12
extern void __VERIFIER_assert(int);
static int calls;
static int narrow(int x) { return x + 1; }
static long same(long x) { return x; }
void *knr() {
  __VERIFIER_assert(calls != 2);
  return 0;
}
int main(void) {
  long (*wide)(long) = (long (*)(long))narrow;
  __VERIFIER_assert(wide(5) == 6);
  ++calls;
  void *(*id)(void *) = (void *(*)(void *))same;
  __VERIFIER_assert(id(&calls) == &calls);
  ++calls;
  void *(*start)(void *) = (void *(*)(void *))knr;
  start(0);
  return 0;
}
