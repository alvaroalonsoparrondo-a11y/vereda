/* A pointer that may hold either address is not folded: the solver still
 * finds the path where it points at a. */
int a, b;

int main()
{
  int *p = nondet_bool() ? &a : &b;
  __ESBMC_assert(!__ESBMC_same_object(p, &a), "p may point at a");
  return 0;
}
// Imported from ESBMC regression/esbmc/same_object_distinct_fold_fail
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^VERIFICATION FAILED$
// MODE: FUTURE
