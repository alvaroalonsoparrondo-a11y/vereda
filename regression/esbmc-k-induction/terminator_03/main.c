int nondet_int();
_Bool nondet_bool();

main()
{
  int x=nondet_int();
  int y=nondet_int();

  if (y>0)
  {
    while(x<100) 
    {
      x=x+y;
     }
  }                           
  //  assert(array[0]>=menor);    
}


// Imported from ESBMC regression/k-induction/terminator_03
// Needs: --k-induction
// RUN: --k-induction -Wno-error=implicit-int
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
