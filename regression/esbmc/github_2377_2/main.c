void main(a, argv) int a;
char **argv;
{
  for (;;)
    if (argv[1])
      break;
}
// Imported from ESBMC regression/esbmc/github_2377_2
// RUN: --unwind 1 --solver z3
// EXPECT: ^VERIFICATION FAILED$
