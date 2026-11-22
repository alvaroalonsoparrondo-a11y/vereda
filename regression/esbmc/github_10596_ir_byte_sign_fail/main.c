// The byte 255 of -1 reads back as the signed char -1 under --ir, not 255.
int main(void)
{
  int a = -1;
  __ESBMC_assert(((char *)&a)[0] == 255, "byte as signed char");
  return 0;
}
// Imported from ESBMC regression/esbmc/github_10596_ir_byte_sign_fail
// Needs: --ir
// RUN: --z3 --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
