// malloc and memset declared without prototypes, so the calls' types differ
// from the declarations: they must still be handled by name.
// RUN: --force-malloc-success
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern void __VERIFIER_assert(int);
char *malloc();
char *memset();

int main(void) {
  char *p = malloc(4);
  memset(p, 3, 4);
  __VERIFIER_assert(p[2] == 3);
  return 0;
}
