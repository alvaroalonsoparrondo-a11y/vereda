// Failing companion to fixedbv-bitcast-ir: same --ir fixedbv->int cast path,
// but the value is nondeterministic so the truncation can violate the claim.
// Exercises the bitcast<fixedbv>(bitvector) -> round_real_to_int path that
// previously aborted on a sort mismatch in mk_lt under --ir.
extern float nondet_float(void);
int main()
{
  float x = nondet_float();
  int n = (int)x;
  __ESBMC_assert(n >= 0, "truncated value need not be non-negative");
  return 0;
}
// Imported from ESBMC regression/esbmc/fixedbv-bitcast-ir_fail
// Needs: --fixedbv --ir
// RUN: --fixedbv --ir --z3 --unwind 5 --no-unwinding-assertions
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
