enum E;

enum E (*f)(void);

int main()
{
}
// Imported from ESBMC regression/esbmc/github_1794
// RUN: --unwind 1
// EXPECT: ^VERIFICATION SUCCESSFUL$
