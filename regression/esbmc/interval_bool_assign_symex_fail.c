_Bool b;

int main()
{
  b = nondet_bool();
  __ESBMC_assume(b);
  b = nondet_bool();

  int i = 0;
  do
  {
    i++;
    if (i > 1)
      break;
  } while (b);

  __ESBMC_assert(i == 2, "i is 1 when the second nondet bool is false");
}
// Imported from ESBMC regression/esbmc/interval_bool_assign_symex_fail
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^VERIFICATION FAILED$
// MODE: FUTURE
