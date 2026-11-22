/* A doubling arithmetic chain flattens to 2^N leaves under
 * canonicalization; the node cap must keep the run fast and the
 * branch must still verify. */
unsigned int __VERIFIER_nondet_u(void);

int main(void)
{
  unsigned int a = __VERIFIER_nondet_u();
  unsigned int c = a;
  for (int i = 0; i < 40; i++)
    c = c + c;
  if ((c & 1u) == 0u)
    __VERIFIER_assert((c & 1u) == 0u); // doubled value is even
  return 0;
}
// Imported from ESBMC regression/esbmc/path_guard_copy_chain_bound
// RUN: --unwind 41 --no-unwinding-assertions
// EXPECT: ^VERIFICATION SUCCESSFUL$
