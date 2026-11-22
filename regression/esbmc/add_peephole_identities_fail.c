// Neighbours of the #626 identities that do not hold. If a fold ever rewrites
// x + x to the wrong shift, or drops the -1 from ~B == -B - 1, one of these
// stops being refutable.
int nondet_int(void);

int main(void)
{
  int x = nondet_int();
  int b = nondet_int();
  __VERIFIER_assert(x + x == (x << 2)); // x + x is not x << 2
  __VERIFIER_assert(~b + 1 == b); // ~b + 1 is not b
  return 0;
}
// Imported from ESBMC regression/esbmc/add_peephole_identities_fail
// EXPECT: ^Generated 2 VCC\(s\), 2 remaining after simplification
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^Generated 2 VCC\(s\), 2 remaining after simplification
// MODE: FUTURE
