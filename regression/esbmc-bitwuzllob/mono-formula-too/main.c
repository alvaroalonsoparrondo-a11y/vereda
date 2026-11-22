int main()
{
  unsigned x = nondet_uint() % 10;
  __ESBMC_assert(x < 10, "x in range");
  return 0;
}
// Imported from ESBMC regression/bitwuzllob/mono-formula-too
// Needs: --bitwuzllob --bitwuzllob-prog fake-mallob.sh
// RUN: --bitwuzllob --bitwuzllob-prog fake-mallob.sh --smt-formula-too
// MODE: FUTURE
// EXPECT: SMT formula written to
// EXPECT: ^VERIFICATION SUCCESSFUL$
