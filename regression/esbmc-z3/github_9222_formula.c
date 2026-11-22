// #9222: the signed and unsigned checks use Z3's no-overflow predicates.
int nondet_int(void);
unsigned nondet_uint(void);
int main(void)
{
  int a = nondet_int(), b = nondet_int();
  unsigned u = nondet_uint(), v = nondet_uint();
  return a * b + (int)(u * v);
}
// Imported from ESBMC regression/z3/github_9222_formula
// Needs: --overflow-check --unsigned-overflow-check
// RUN: --z3 --overflow-check --unsigned-overflow-check --smt-formula-only
// MODE: FUTURE
// EXPECT: bvsmul_noovfl
// EXPECT: bvsmul_noudfl
// EXPECT: bvumul_noovfl
