/* #10504: the call trace names functions by source name and follows the
   violated-property block. */
#include <assert.h>
int __VERIFIER_nondet_int(void);
int g;
void setup(int v) { g = v; }
void check(void) { assert(g != 3); }
int main(void)
{
  setup(__VERIFIER_nondet_int());
  check();
  return 0;
}
// Imported from ESBMC regression/esbmc/github_10504
// Needs: --show-funccall-trace
// RUN: --show-funccall-trace
// MODE: FUTURE
// EXPECT: ^Violated property:\n  file \S*github_10504\.c line 7 column 20 function check\n  assertion g != 3\n  .*\nFunction call trace:\n  main at file \S*github_10504\.c line 8 column 1\n  setup at file \S*github_10504\.c line 10 column 3 function main\n  check at file \S*github_10504\.c line 11 column 3 function main$
// EXPECT: ^VERIFICATION FAILED$
