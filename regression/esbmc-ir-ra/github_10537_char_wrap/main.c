/* Under --ir integers are unbounded: folding 255 + 1 must not wrap to 0. */
int main()
{
  unsigned char c = 255;
  c = c + 1;
  __ESBMC_assert((int)c == 256, "no wrap under --ir");
  return 0;
}
// Imported from ESBMC regression/ir-ra/github_10537_char_wrap
// Needs: --ir
// RUN: --ir --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
