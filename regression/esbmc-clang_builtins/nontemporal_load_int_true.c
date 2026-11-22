int main() {
  int expected = nondet_int();
  int actual = __builtin_nontemporal_load(&expected);
  __ESBMC_assert(expected == actual, "check");
  return 0;
}
// Imported from ESBMC regression/clang_builtins/nontemporal_load_int_true
// RUN: --force-malloc-success
// EXPECT: ^VERIFICATION SUCCESSFUL$
