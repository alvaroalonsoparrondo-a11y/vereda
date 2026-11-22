/* A cast along the path -- here `void *sub` forces a real one -- used to lose
 * the root: the target fell back to direct_targets, matched no snapshot, and
 * the function generated ZERO VCCs, so this frame violation verified. */
typedef struct { int a; int b; } Inner;
typedef struct { void *sub; int x; } Outer;

void write_sub_a(Outer *o, int v)
{
  __ESBMC_requires(__ESBMC_is_fresh(o, sizeof(*o)));
  __ESBMC_requires(o != (void *)0 && o->sub != (void *)0);
  __ESBMC_assigns(((Inner *)o->sub)->a);
  __ESBMC_ensures(1);
  ((Inner *)o->sub)->a = v;
  o->x = 99; /* not in __ESBMC_assigns: a frame violation */
}

int main()
{
  return 0;
}
// Imported from ESBMC regression/function_contract/github_7055_assigns_multilevel_cast_fail
// Needs: --enforce-contract write_sub_a
// RUN: --enforce-contract write_sub_a --function write_sub_a --no-pointer-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^.*o->x not in assigns clause.*$
