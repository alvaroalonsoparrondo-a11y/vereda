// Objects on exclusive branches take no address space on the other branch,
// and a request above PTRDIFF_MAX returns null instead of ending the path.
// EXPECT: ^VERIFICATION FAILED$
extern int __VERIFIER_nondet_int(void);
extern void __VERIFIER_error(void);
extern void *malloc(unsigned long);

int main(void) {
  void *p;
  if (__VERIFIER_nondet_int())
    p = malloc(1UL << 63);
  else
    p = malloc(1UL << 63);
  __VERIFIER_error();
  return 0;
}
