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
  b[1] = 7;
  clr(b);
  __ESBMC_assert(b[1] == 7, "b[1] survived the replaced call");
  return 0;
}
// Imported from ESBMC regression/function_contract/github_6961_assigns_ptr_param_valuesets_fail
// Needs: --replace-call-with-contract clr --add-symex-value-sets
// RUN: --replace-call-with-contract clr --unwind 10 --add-symex-value-sets
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
