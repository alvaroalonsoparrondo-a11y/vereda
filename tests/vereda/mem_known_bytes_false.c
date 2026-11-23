// A nondet store over bytes known at constant addresses still reaches them.
// EXPECT: ^Violated property:\n  file \S*mem_known_bytes_false\.c line 18 column 3 function main\n  __VERIFIER_assert\n  a\[2\] == 9 \|\| g == 1$
// EXPECT: ^VERIFICATION FAILED$
extern int __VERIFIER_nondet_int(void);
extern void __VERIFIER_assume(int);
extern void __VERIFIER_assert(int);

int g = 1;
int a[4];

int main(void) {
  if (__VERIFIER_nondet_int())
    g = 2;
  a[2] = 9;
  int i = __VERIFIER_nondet_int();
  __VERIFIER_assume(i >= 0 && i < 4);
  a[i] = 3;
  __VERIFIER_assert(a[2] == 9 || g == 1);
  return 0;
}
