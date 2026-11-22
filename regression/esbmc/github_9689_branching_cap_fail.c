/* Issue #9689: the YAML witness must not carry one branching waypoint per
   executed branch. */
unsigned nondet_uint(void);
int main(void)
{
  unsigned n = nondet_uint();
  int s = 0;
  for (int i = 0; i < 1500; i++)
    if ((i ^ n) % 2)
      s++;
  __ESBMC_assert(s != 750, "reached");
  return 0;
}
// Imported from ESBMC regression/esbmc/github_9689_branching_cap_fail
// Needs: --witness-output-yaml -
// RUN: --witness-output-yaml - --unwind 1600 --no-unwinding-assertions
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: (?s)\A(?:(?!type: "branching").)*(?:type: "branching"(?:(?!type: "branching").)*){1,1000}\Z
