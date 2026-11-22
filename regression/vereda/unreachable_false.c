// A reachable __builtin_unreachable is a failed check, as in ESBMC.
// EXPECT: ^Violated property:\n  file \S*unreachable_false\.c line 10 column 5 function main\n  __builtin_unreachable$
// EXPECT: ^VERIFICATION FAILED$
extern int __VERIFIER_nondet_int(void);

int main(void) {
  int x = __VERIFIER_nondet_int();
  if (x == 5)
    // ponytail: keep the call on line 10; the EXPECT above names it.
    __builtin_unreachable();
  return 0;
}
