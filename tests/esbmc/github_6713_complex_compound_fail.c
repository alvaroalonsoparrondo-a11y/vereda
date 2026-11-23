/* `*=` by a real scalar scales both components. Expecting the imaginary part
   to survive unchanged has to be refuted, or the lowering is dropping it
   (#6713). */
int main(void)
{
  _Complex float a = 3.0f + 4.0fi;
  a *= 2.0f;
  __VERIFIER_assert(__imag__ a == 4.0f); // imag must have doubled too
  return 0;
}
// Imported from ESBMC regression/esbmc/github_6713_complex_compound_fail
// RUN: --incremental-bmc
// EXPECT: ^VERIFICATION FAILED$
