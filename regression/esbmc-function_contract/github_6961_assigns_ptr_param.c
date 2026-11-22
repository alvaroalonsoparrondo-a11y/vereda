#define N 4

void clr(int *p)
{
  __ESBMC_assigns(p);
  __ESBMC_ensures(p[0] == 0);

  for (int i = 0; i < N; i++)
    p[i] = 0;
}

int main(void)
{
  int b[N];
  b[0] = 1;
  clr(b);
  __VERIFIER_assert(b[0] == 0); // callee zeroed the first element
  return 0;
}
// Imported from ESBMC regression/function_contract/github_6961_assigns_ptr_param
// Needs: --replace-call-with-contract clr
// RUN: --replace-call-with-contract clr --unwind 10
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
