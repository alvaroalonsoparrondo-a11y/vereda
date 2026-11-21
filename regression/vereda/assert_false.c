// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^Violated property:\n  file \S*assert_false\.c line 9 column 3 function main\n  __VERIFIER_assert$
// A declared __VERIFIER_assert is a check: x == 3 is possible.
extern int __VERIFIER_nondet_int(void);
extern void __VERIFIER_assert(int);

int main(void) {
  int x = __VERIFIER_nondet_int();
  __VERIFIER_assert(x != 3);
  return 0;
}
