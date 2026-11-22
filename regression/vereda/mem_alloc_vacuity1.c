// An allocation's size must not constrain paths that never allocate: the
// error before malloc(n) is reachable with n == SIZE_MAX.
// EXPECT: ^VERIFICATION FAILED$
extern unsigned long __VERIFIER_nondet_ulong(void);
extern void __VERIFIER_error(void);
extern void *malloc(unsigned long);

int main(void) {
  unsigned long n = __VERIFIER_nondet_ulong();
  if (n == (unsigned long)-1)
    __VERIFIER_error();
  char *p = malloc(n);
  return 0;
}
