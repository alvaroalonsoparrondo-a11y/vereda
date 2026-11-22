int main()
{
 int a,*q;
 a = 1;
 q = &a;
 *q = 2;
 __ESBMC_assert(a == 2, "");
}
// Imported from ESBMC regression/esbmc/interval-analysis-ptr
// Needs: --interval-analysis
// RUN: --interval-analysis
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
