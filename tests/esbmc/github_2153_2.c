// Variant of github_2153: byte-manipulation via struct-field pointer cast
// at a non-zero byte offset.  After ptr[1] = nondet_char(), bug.bar can
// represent any pointer value, so the assertion must fail.

struct
{
  void *bar;
} bug;

int some_var;

int main()
{
  char *ptr = (char *)&bug.bar;
  ptr[1] = __VERIFIER_nondet_char();

  __VERIFIER_assert(bug.bar != &some_var);
}
// Imported from ESBMC regression/esbmc/github_2153_2
// RUN: --no-unwinding-assertions --unwind 1
// EXPECT: ^VERIFICATION FAILED$
