int main()
{
  unsigned x = __VERIFIER_nondet_uint() % 10;
  __VERIFIER_assert(x < 10); // x in range
  return 0;
}
// Imported from ESBMC regression/neurosym/ir-rejected
// Needs: --neurosym --ir
// RUN: --neurosym --ir
// MODE: FUTURE
// EXPECT: bit-vector-only
