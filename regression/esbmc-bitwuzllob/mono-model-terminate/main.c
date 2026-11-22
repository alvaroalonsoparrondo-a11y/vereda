int main()
{
  unsigned x = nondet_uint() % 10;
  __ESBMC_assert(x < 10, "x in range");
  return 0;
}
// Imported from ESBMC regression/bitwuzllob/mono-model-terminate
// Needs: --bitwuzllob --bitwuzllob-prog fake-mallob.sh --bitwuzllob-model-prog z3 -in
// RUN: --bitwuzllob --bitwuzllob-prog fake-mallob.sh --bitwuzllob-model-prog "z3 -in"
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
