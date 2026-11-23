// A malloc that cannot be satisfied returns null and the path goes on, even
// with --force-malloc-success, as in ESBMC.
// RUN: --force-malloc-success
// EXPECT: ^VERIFICATION FAILED$
extern unsigned long __VERIFIER_nondet_ulong(void);
extern void __VERIFIER_error(void);
extern void *malloc(unsigned long);

int main(void) {
  unsigned long n = __VERIFIER_nondet_ulong();
  char *p = malloc(n);
  if (n == (unsigned long)-1 && p == 0)
    __VERIFIER_error();
  return 0;
}
