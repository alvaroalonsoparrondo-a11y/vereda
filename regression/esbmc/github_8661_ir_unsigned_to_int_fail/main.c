unsigned nondet_uint();
int main(void)
{
  unsigned u = nondet_uint();
  __ESBMC_assume(u == 3000000000u);
  int x = (int)u;
  return x;
}
// Imported from ESBMC regression/esbmc/github_8661_ir_unsigned_to_int_fail
// Needs: --overflow-check --ir
// RUN: --overflow-check --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^\s*FAILED\s+\[main\.cast-arithmetic-overflow\.1\]\s+line\s+6\s+Cast arithmetic overflow on typecast$
