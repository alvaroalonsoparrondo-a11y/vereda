int main()
{
  int x;

  x = 5;

  __ESBMC_assert(__ESBMC_exists(&x, x == 13), "exists eq");
}
// Imported from ESBMC regression/bitwuzla/github_7024_exists
// RUN: --solver bitwuzla
// EXPECT: ^VERIFICATION SUCCESSFUL$
