int main()
{
  int i, j, k;
  
  i=nondet_int();
  k=nondet_int();
  
  if(i)
  {
  }
  else
  {
    if(k)
    {
      assert(0);
    }
  }
}
// Imported from ESBMC regression/cbmc/01_cbmc_if2
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^VERIFICATION FAILED$
// MODE: FUTURE
