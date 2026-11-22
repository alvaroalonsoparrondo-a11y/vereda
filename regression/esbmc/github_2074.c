/* #2074: --function leaves the entry point's arguments nil, and interval
 * analysis dereferenced them. */
int f(unsigned char x)
{
  __ESBMC_assert(x <= 255, "x fits in a byte");
  return x;
}
// Imported from ESBMC regression/esbmc/github_2074
// Needs: --interval-analysis
// RUN: --function f --interval-analysis
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
