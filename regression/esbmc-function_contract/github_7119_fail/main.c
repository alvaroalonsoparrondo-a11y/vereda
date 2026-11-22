/* github #7119: a violated requires with __ESBMC_forall printed a raw irep
 * dump. The guard has no lower bound, so j_bound = -1 violates it. */
typedef short int16_t;
#define N 4
typedef struct
{
  int16_t coeffs[N];
} poly;
int j_bound;

void add(poly *r)
{
  __ESBMC_requires(r != 0);
  __ESBMC_requires(__ESBMC_forall(
    &j_bound,
    !(j_bound < N) ||
      (r->coeffs[j_bound] > -6658 && r->coeffs[j_bound] < 6658)));
  __ESBMC_ensures(1);
  __ESBMC_assigns(r->coeffs);
  r->coeffs[0] = 0;
}

int main(void)
{
  poly r = {{0, 0, 0, 0}};
  add(&r);
  return 0;
}
// Imported from ESBMC regression/function_contract/github_7119_fail
// Needs: --replace-call-with-contract add
// RUN: --replace-call-with-contract add --unwind 5
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^  contract requires$
// EXPECT: ^  &r != 0 && \(__ESBMC_forall\(\(void \*\)\(&j_bound\), !\(j_bound < 4\) \|\| .*\)\)$
