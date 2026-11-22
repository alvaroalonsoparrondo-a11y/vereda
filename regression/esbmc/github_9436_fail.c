int main(void)
{
  unsigned char c = 1;
  c <<= 32;
  return c;
}
// Imported from ESBMC regression/esbmc/github_9436_fail
// Needs: --ub-shift-check
// RUN: --ub-shift-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: undefined behavior on shift operation shl$
