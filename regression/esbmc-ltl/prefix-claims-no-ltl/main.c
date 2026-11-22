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
// Imported from ESBMC regression/ltl/prefix-claims-no-ltl
// RUN: -DLTL_PREFIX_BOUND=10 --multi-property
// FILES: test.ba-2.c
// EXPECT: Solving claim 'LTL_BAD
// EXPECT: Solving claim 'LTL_FAILING
// EXPECT: Solving claim 'LTL_SUCCEEDING
// EXPECT: ^ +FAILED .*LTL_FAILING$
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: Solving claim 'LTL_BAD
// MODE: FUTURE
