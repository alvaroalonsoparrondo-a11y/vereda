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
// Imported from ESBMC regression/ltl/basic-no-monitor
// Needs: --ltl
// RUN: --ltl
// MODE: FUTURE
// EXPECT: ^VERIFICATION UNKNOWN$
// EXPECT: ^WARNING: No LTL outcome seen; the property was not checked$
