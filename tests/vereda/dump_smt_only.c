// --dump-smt-only prints the walk's formula with the checks' disjunction
// asserted and stops before solving.
// RUN: --dump-smt-only --unwind 2
// EXPECT: ^\(declare-const \|nondet@
// EXPECT: ^\(assert
// EXPECT: ^\(check-sat\)
// EXPECT-NOT: Solving|VERIFICATION
extern void __VERIFIER_assert(int);
extern int nondet(void);
int main(void) {
  int x = nondet();
  __VERIFIER_assert(x != 7);
  return 0;
}
