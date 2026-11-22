int main()
{
  unsigned x = nondet_uint() % 10;
  __ESBMC_assert(x < 10, "x in range");
  return 0;
}
// Imported from ESBMC regression/bitwuzllob/mono-model-dead-safe
// Needs: --bitwuzllob --bitwuzllob-prog always-unsat-mallob.sh --bitwuzllob-model-prog dead-model.sh
// RUN: --bitwuzllob --bitwuzllob-prog always-unsat-mallob.sh --bitwuzllob-model-prog dead-model.sh
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
