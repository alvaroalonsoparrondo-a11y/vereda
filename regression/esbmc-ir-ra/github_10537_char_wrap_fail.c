/* The unwrapped value is still checked: 255 + 1 is 256, not 0. */
int main()
{
  unsigned char c = 255;
  c = c + 1;
  __VERIFIER_assert((int)c == 0); // wrapped value
  return 0;
}
// Imported from ESBMC regression/ir-ra/github_10537_char_wrap_fail
// Needs: --ir
// RUN: --ir --z3
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
