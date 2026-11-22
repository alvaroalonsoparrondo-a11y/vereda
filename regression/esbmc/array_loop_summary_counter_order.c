// Another counter's update follows the loop counter's.
unsigned nondet_uint(void);
int main() {
  unsigned x = nondet_uint();
  unsigned y = x;
  while (x < 100) { x++; y++; }
  __ESBMC_assert(x == y, "");
}
// Imported from ESBMC regression/esbmc/array_loop_summary_counter_order
// Needs: --summarize-array-loops
// RUN: --summarize-array-loops
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
