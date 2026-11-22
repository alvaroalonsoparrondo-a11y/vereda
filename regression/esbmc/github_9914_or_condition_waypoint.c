// An operand of || gets no branching waypoint: its own direction is not the
// condition's. A lone condition keeps its waypoint.
int nondet_int();

int main()
{
  int a = nondet_int(), b = nondet_int();
  if (a > 0 || nondet_int())
    return 0;
  if (b > 3)
    b = 0;
  __VERIFIER_assert(b != 0); // reached
  return 0;
}
// Imported from ESBMC regression/esbmc/github_9914_or_condition_waypoint
// Needs: --witness-output-yaml -
// RUN: --witness-output-yaml -
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: (?s)type: "branching"(?:(?!type:).)*?^\s+line: 10$
// EXPECT: (?s)\A(?!.*type: "branching"(?:(?!type:).)*?^\s+line: 8$)
