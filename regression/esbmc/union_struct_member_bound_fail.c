struct p
{
  int n;
};

union u
{
  struct p a;
  int b;
};

struct x
{
  union u u;
};

int main(void)
{
  union u u;
  u.a.n = 4;
  struct x x;
  x.u.a.n = 4;

  int s = 0;
  for (int i = 0; i < u.a.n; i++)
    s++;
  for (int i = 0; i < x.u.a.n; i++)
    s++;

  __ESBMC_assert(s == 9, "the loops run one time too many");
  return 0;
}
// Imported from ESBMC regression/esbmc/union_struct_member_bound_fail
// EXPECT: ^\s+the loops run one time too many$
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^\s+the loops run one time too many$
// MODE: FUTURE
