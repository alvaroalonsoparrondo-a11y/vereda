// A callee that aborts on some paths: only returning paths continue.
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern int __VERIFIER_nondet_int(void);
extern void __VERIFIER_assert(int);
extern void abort(void);

int positive(int x) {
  if (x <= 0)
    abort();
  return x;
}

int main(void) {
  int y = positive(__VERIFIER_nondet_int());
  __VERIFIER_assert(y > 0);
  return 0;
}
