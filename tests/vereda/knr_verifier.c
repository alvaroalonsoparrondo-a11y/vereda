// Verifier functions declared without a prototype, as many SV-COMP tasks do:
// the call's type differs from the declaration's, and they must still work.
// EXPECT: ^Violated property:\n  file \S*knr_verifier\.c line 11 column 3 function main\n  __VERIFIER_assert\n  x != 3$
// EXPECT: ^VERIFICATION FAILED$
extern int __VERIFIER_nondet_int();
extern void __VERIFIER_assume();
extern void __VERIFIER_assert();

int main() {
  int x = __VERIFIER_nondet_int();
  __VERIFIER_assert(x != 3);
  return 0;
}
