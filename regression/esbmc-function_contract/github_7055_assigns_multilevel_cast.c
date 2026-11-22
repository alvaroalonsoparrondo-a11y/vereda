/* The positive half of the cast case: stripping the cast must recover the root
 * without widening the frame, so a body writing only what the clause names
 * still verifies. */
typedef struct { int a; int b; } Inner;
typedef struct { void *sub; int x; } Outer;

void write_sub_a(Outer *o, int v)
{
  __ESBMC_requires(__ESBMC_is_fresh(o, sizeof(*o)));
  __ESBMC_requires(o != (void *)0 && o->sub != (void *)0);
  __ESBMC_assigns(((Inner *)o->sub)->a);
  __ESBMC_ensures(1);
  ((Inner *)o->sub)->a = v;
}

int main()
{
  return 0;
}
// Imported from ESBMC regression/function_contract/github_7055_assigns_multilevel_cast
// Needs: --enforce-contract write_sub_a
// RUN: --enforce-contract write_sub_a --function write_sub_a --no-pointer-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
