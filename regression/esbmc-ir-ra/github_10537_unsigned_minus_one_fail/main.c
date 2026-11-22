int main()
{
  /* Under --ir, converting -1 to unsigned does not wrap to UINT_MAX. */
  unsigned u = -1;
  __ESBMC_assert(u > 5, "u > 5");
  return 0;
}
// Imported from ESBMC regression/ir-ra/github_10537_unsigned_minus_one_fail
// Needs: --ir
// RUN: --ir --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: u > 5
