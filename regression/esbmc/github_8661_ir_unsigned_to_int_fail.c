unsigned __VERIFIER_nondet_uint();
int main(void)
{
  unsigned u = __VERIFIER_nondet_uint();
  __VERIFIER_assume(u == 3000000000u);
  int x = (int)u;
  return x;
}
// Imported from ESBMC regression/esbmc/github_8661_ir_unsigned_to_int_fail
// Needs: --overflow-check --ir
// RUN: --overflow-check --ir
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^\s*FAILED\s+\[github_8661_ir_unsigned_to_int_fail\.cast-arithmetic-overflow\.1\]\s+line\s+6\s+Cast arithmetic overflow on typecast$
