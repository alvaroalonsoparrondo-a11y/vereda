float nondet_float();

int main()
{
  float x = nondet_float();
  assert(x==x);
  return 0;
}
// Imported from ESBMC regression/floats/nan_float
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^VERIFICATION FAILED$
// MODE: FUTURE
