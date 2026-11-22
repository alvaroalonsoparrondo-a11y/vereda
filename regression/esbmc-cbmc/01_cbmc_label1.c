int g=0;

int f()
{
  assert(g==0);
  g++;
}

int main()
{
  l:
  l2:
  {
    int i=f();
    goto l;
  }
}
// Imported from ESBMC regression/cbmc/01_cbmc_label1
// RUN: --unwind 1
// EXPECT: ^VERIFICATION FAILED$
