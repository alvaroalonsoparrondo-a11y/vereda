// A variable-length array's size must not constrain the path before it.
// EXPECT: ^VERIFICATION FAILED$
extern unsigned long __VERIFIER_nondet_ulong(void);
extern void __VERIFIER_error(void);

int main(void) {
  unsigned long n = __VERIFIER_nondet_ulong();
  if (n > (1UL << 62))
    __VERIFIER_error();
  int a[n];
  a[0] = 1;
  return a[0];
}
