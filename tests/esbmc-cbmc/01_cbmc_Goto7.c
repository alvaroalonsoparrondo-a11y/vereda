short f0(short x)
{
  int z;

  do {
    z=0;
    if(x <= 0) { z=1;
      return 100; }
  }
  while( x-- ); /* <-- The diff */

  z=2;
  return 200;
}

short f1(short x)
{
  do {
    if(x <= 0)
      return 100;
  }
  while( --x ); /* <-- The diff */

  return 200;
}

int main()
{
  int flag;
  short a;
  short res0, res1;

  if( flag )
    a = 1;
  else
    a = 1;

  res0 = f0(a);
  res1 = f1(a);

  assert(res0 == res1); /* <-- should fail */
  
  return 0;
}
// Imported from ESBMC regression/cbmc/01_cbmc_Goto7
// RUN: --unwind 2
// EXPECT: ^VERIFICATION FAILED$
