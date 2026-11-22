int main()
{
  unsigned x = nondet_uint() % 10;
  __ESBMC_assert(x < 5, "x less than five");
  return 0;
}
// Imported from ESBMC regression/bitwuzllob/mono-unsafe
// Needs: --bitwuzllob --bitwuzllob-prog fake-mallob.sh --bitwuzllob-model-prog z3 -in
// RUN: --bitwuzllob --bitwuzllob-prog fake-mallob.sh --bitwuzllob-model-prog "z3 -in"
// MODE: FUTURE
// EXPECT: ^\[Counterexample\]$
// EXPECT: ^VERIFICATION FAILED$
