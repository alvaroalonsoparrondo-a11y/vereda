int pressed, charge, min;

int main()
{
	charge = nondet_int();
	min = nondet_int() % 1024;
	for (int i = 0; i < 2; i++) {
		pressed = nondet_int();
		if (pressed)
			charge = min + 1;
	}
}
// Imported from ESBMC regression/ltl/basic-success
// Needs: --ltl
// RUN: --ltl test-neg.ba-2.c -DLTL_PREFIX_BOUND=10
// FILES: test-neg.ba-2.c
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
// EXPECT: ^Final lowest outcome: LTL_SUCCEEDING$
