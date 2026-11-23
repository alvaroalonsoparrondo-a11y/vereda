// Function pointers in a global initialiser, called by index, compared and
// passed on; a constant pointer reaches only its own function.
// RUN: --unwind 3
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern void __VERIFIER_assert(int);
extern unsigned nondet(void);
typedef int (*op)(int, int);
static int add(int a, int b) { return a + b; }
static int sub(int a, int b) { return a - b; }
static int apply(op f, int a, int b) { return f(a, b); }
static op table[2] = {add, sub};
int main(void) {
  unsigned i = nondet() % 2;
  int r = table[i](5, 3);
  __VERIFIER_assert(i == 0 ? r == 8 : r == 2);
  __VERIFIER_assert(table[0] == add && table[1] != add);
  __VERIFIER_assert(apply(sub, 1, 1) == 0);
  return 0;
}
