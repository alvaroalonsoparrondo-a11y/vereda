void foo(char **q)
{
    q[5];
}

int main(int argc, char **argv)
{
    int a;
    __VERIFIER_assume(a >= 5 && a <= 20);
    char *b[2][a + 1]; // notice that this is now a 2d array, was 1d before
    foo(b[0]);
    return 0;
}
// Imported from ESBMC regression/esbmc/github_2360
// RUN: --unwind 1
// EXPECT: ^VERIFICATION SUCCESSFUL$
