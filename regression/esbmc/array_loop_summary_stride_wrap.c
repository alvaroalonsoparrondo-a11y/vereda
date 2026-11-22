// With n near UINT_MAX, i += 2 wraps before reaching n, so no closed form
// holds: the loop must stay.
unsigned nondet_uint(void);
int main() {
  unsigned n = nondet_uint();
  unsigned i;
  for (i = 0; i < n; i += 2)
    ;
  __VERIFIER_assert(i >= n);
}
// Imported from ESBMC regression/esbmc/array_loop_summary_stride_wrap
// RUN: --unwind 2 --no-unwinding-assertions
// EXPECT: ^VERIFICATION SUCCESSFUL$
