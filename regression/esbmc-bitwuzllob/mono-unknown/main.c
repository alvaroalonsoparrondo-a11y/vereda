int main()
{
  unsigned x = nondet_uint() % 10;
  __ESBMC_assert(x < 10, "x in range");
  return 0;
}
// Imported from ESBMC regression/bitwuzllob/mono-unknown
// Needs: --bitwuzllob --bitwuzllob-prog unknown-mallob.sh --result-only
// RUN: --bitwuzllob --bitwuzllob-prog unknown-mallob.sh --result-only
// MODE: FUTURE
// EXPECT: solver returned unknown
// EXPECT: SMT solver failed
