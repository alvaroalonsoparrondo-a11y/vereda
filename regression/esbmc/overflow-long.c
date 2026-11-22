
int main()
{
int a = -136;
int v = 32;
int dl = (long)v * (long)a;
}
// Imported from ESBMC regression/esbmc/overflow-long
// Needs: --overflow-check
// RUN: --overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
