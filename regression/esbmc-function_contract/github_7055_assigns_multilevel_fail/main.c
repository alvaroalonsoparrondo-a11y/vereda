/* A path through more than one pointer used to reach neither check: it was not
 * a `ptr->field` the per-field machinery recognises, and recording it as a
 * direct target matched no snapshot, so the function generated ZERO VCCs and a
 * body writing outside its frame verified. */
typedef struct { int a; int b; } Inner;
typedef struct { Inner *sub; int x; } Outer;

void write_sub_a(Outer *o, int v)
{
  __ESBMC_requires(__ESBMC_is_fresh(o, sizeof(*o)));
  __ESBMC_requires(o != (void *)0 && o->sub != (void *)0);
  __ESBMC_assigns(o->sub->a);
  __ESBMC_ensures(1);
  o->sub->a = v;
  o->x = 99; /* not in __ESBMC_assigns: a frame violation */
}

int main()
{
  return 0;
}
// Imported from ESBMC regression/function_contract/github_7055_assigns_multilevel_fail
// Needs: --enforce-contract write_sub_a
// RUN: --enforce-contract write_sub_a --function write_sub_a --no-pointer-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^.*o->x not in assigns clause.*$
