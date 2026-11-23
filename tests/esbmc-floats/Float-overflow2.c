int main()
{
  float f=1;

  for(int i=0; i<128; i++)
    f*=2; // overflows in the last iteration
}
// Imported from ESBMC regression/floats/Float-overflow2
// Needs: --overflow-check
// RUN: --floatbv --overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
