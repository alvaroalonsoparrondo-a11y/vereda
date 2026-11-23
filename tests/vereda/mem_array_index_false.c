// A nondet index into an initialised array finds the element that breaks
// the assertion.
// EXPECT: ^Violated property:\n  file \S*mem_array_index_false\.c line 13 column 3 function main\n  __VERIFIER_assert\n  a\[i\] != 30$
// EXPECT: ^VERIFICATION FAILED$
extern int __VERIFIER_nondet_int(void);
extern void __VERIFIER_assume(int);
extern void __VERIFIER_assert(int);

int main(void) {
  int a[4] = {10, 20, 30, 40};
  int i = __VERIFIER_nondet_int();
  __VERIFIER_assume(i >= 0 && i < 4);
  __VERIFIER_assert(a[i] != 30);
  return 0;
}
