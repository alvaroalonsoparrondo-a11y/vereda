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
// Imported from ESBMC regression/ltl/basic
// Needs: --ltl
// RUN: --ltl test.ba-2.c -DLTL_PREFIX_BOUND=10
// FILES: test.ba-2.c
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^Final lowest outcome: LTL_FAILING$
