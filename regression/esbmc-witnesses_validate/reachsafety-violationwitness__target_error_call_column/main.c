int main(void)
{
  ERROR: __ESBMC_assert(0, "error label");
}
// Imported from ESBMC regression/witnesses_validate/reachsafety-violationwitness/target_error_call_column
// Needs: --enable-unreachability-intrinsic --error-label ERROR --validate-violation-witness --witness witness.yml
// RUN: --enable-unreachability-intrinsic --error-label ERROR --validate-violation-witness --witness witness.yml
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
