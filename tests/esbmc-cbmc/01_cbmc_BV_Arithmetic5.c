unsigned int test_log2(unsigned int v)
{
  unsigned c = 0; // c will be lg(v)
  while (v >>= 1) 
    {
      c++;
    }
  return c;
}

int main()
{
  int r;
  
  r=test_log2(128);
  assert(r==7);
}
// Imported from ESBMC regression/cbmc/01_cbmc_BV_Arithmetic5
// RUN: --unwind 32
// EXPECT: ^VERIFICATION SUCCESSFUL$
