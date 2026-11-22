int nondet_int(void);

int main(void)
{
  int x = nondet_int(), y = nondet_int();

  /* Both operands of the outer == are boolean; the usual arithmetic
     conversions promote them to int before it compares them. */
  __ESBMC_assert((-x == -y) == (x == y), "negation preserves equality");
  return 0;
}
// Imported from ESBMC regression/esbmc/irep2_only_rel_bool_operands
// Needs: --goto-functions-only --clang-c-irep2-adjust-only
// RUN: --goto-functions-only --clang-c-irep2-adjust-only
// MODE: FUTURE
// EXPECT: ASSERT \(\(signed int\)\(-x == -y\)\) == \(\(signed int\)\(x == y\)\)
