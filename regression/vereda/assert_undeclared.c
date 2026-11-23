// assert called without <assert.h> is an implicitly declared function; as
// in ESBMC it is the assertion it was meant to be, at the caller's line.
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: line 9
extern int __VERIFIER_nondet_int(void);
int main(void) {
  int x = __VERIFIER_nondet_int();
  if (x > 3)
    assert(x != 5);
  return 0;
}
