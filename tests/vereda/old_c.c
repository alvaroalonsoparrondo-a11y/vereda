// Old C as SV-COMP's CIL and kernel tasks write it: an integer as a pointer,
// a pointer as an integer, and mismatched function pointer types. Clang 15
// and later reject these unless the driver relaxes them, as ESBMC does.
// EXPECT-NOT: error:
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern void __VERIFIER_assert(int);
typedef long (*handler_t)(void *, unsigned char);
static long handle(int *p, unsigned char c) { return c; }

int main(void) {
  handler_t h = handle;
  int sentinel = (void *)0;
  void *q = 0xffUL;
  __VERIFIER_assert(sentinel == 0);
  return 0;
}
