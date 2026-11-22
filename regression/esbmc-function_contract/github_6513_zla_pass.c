// Skipping the zero-length member must not cost the wrapper its ability to
// discharge a contract that genuinely holds (#6513).
typedef struct
{
  int len;
  int data[0];
} buf_t;

int g;

void f(buf_t *b)
{
  __ESBMC_requires(__ESBMC_is_fresh(b, sizeof(*b)));
  __ESBMC_requires(b != 0);
  __ESBMC_assigns(g);
  __ESBMC_ensures(g == 1);
  g = 1;
}

int main()
{
  return 0;
}
// Imported from ESBMC regression/function_contract/github_6513_zla_pass
// Needs: --enforce-contract f
// RUN: --enforce-contract f --function f
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
