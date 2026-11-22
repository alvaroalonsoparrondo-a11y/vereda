int test_bit_parity(unsigned int v)
{
  int parity = 0;
  while (v)
    {
      parity ^= (v & 1);
      v >>= 1;
    }
  return parity;
}

int main()
{
  int r0, r1;

  r0=test_bit_parity(699050);
  assert(r0==0);

  r1=test_bit_parity(699050+1);  
  assert(r1==1);
}
// Imported from ESBMC regression/cbmc/01_cbmc_BV_Arithmetic2
// RUN: --unwind 32
// EXPECT: ^VERIFICATION SUCCESSFUL$
