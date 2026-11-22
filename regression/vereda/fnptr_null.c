// A call through a pointer that is no function of this program goes to an
// unknown function, as ESBMC's open world has it: the path goes on and the
// result is unconstrained.
// RUN: --unwind 2
// EXPECT: no body for function __vereda_unknown_target
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: line 16
extern void __VERIFIER_assert(int);
extern int (*callback)(int);
static int one(void) { return 1; }
int main(void) {
  int (*f)(void) = 0;
  f();
  int r = callback(1);
  __VERIFIER_assert(one() == 1);
  __VERIFIER_assert(r == 0);
  return 0;
}
