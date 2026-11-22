int main() {
  int expected = nondet_int();
  int actual = __builtin_nontemporal_load(&expected);
  expected++;
  __ESBMC_assert(expected == actual, "check");
  return 0;
}
// Imported from ESBMC regression/clang_builtins/nontemporal_load_int_false
// RUN: --force-malloc-success
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^VERIFICATION FAILED$
// MODE: FUTURE
