double nondet_double();

int main()
{
  double x = nondet_double();
  assert(x==x);
  return 0;
}
// Imported from ESBMC regression/floats/nan_double
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^VERIFICATION FAILED$
// MODE: FUTURE
