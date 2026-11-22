// A declaration that disagrees with the definition in another file: the call
// converts its arguments to the definition's types, as a call through a
// pointer of another type does, so the long argument is cut to an int.
// FILES: g.c
// RUN: -m64
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern void __VERIFIER_assert(int);
int g(long a);

int main(void) {
  __VERIFIER_assert(g(1) == 1);
  __VERIFIER_assert(g(0x100000002L) == 2);
  return 0;
}
