int main()
{
  unsigned x = nondet_uint() % 10;
  __ESBMC_assert(x < 10, "x in range");
  return 0;
}
// Imported from ESBMC regression/bitwuzllob/mono-incompatible-strategy
// Needs: --bitwuzllob --k-induction --bitwuzllob-prog fake-mallob.sh
// RUN: --bitwuzllob --k-induction --bitwuzllob-prog fake-mallob.sh
// MODE: FUTURE
// EXPECT: does not support --k-induction
