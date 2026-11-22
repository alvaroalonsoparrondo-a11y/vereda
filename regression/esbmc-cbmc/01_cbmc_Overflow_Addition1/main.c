int main() {
  signed int i;
  
  i++;
}
// Imported from ESBMC regression/cbmc/01_cbmc_Overflow_Addition1
// Needs: --overflow-check
// RUN: --overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
