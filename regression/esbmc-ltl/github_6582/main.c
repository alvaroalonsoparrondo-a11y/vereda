int s;

int main()
{
	s = 0;
	s = 1;
	s = 0;
	return 0;
}
// Imported from ESBMC regression/ltl/github_6582
// Needs: --ltl
// RUN: --ltl safety.c -DLTL_PREFIX_BOUND=6
// FILES: safety.c
// MODE: FUTURE
// EXPECT: ^WARNING: monitor has no __ESBMC_switch_from_monitor\(\) call; regenerate it with
// EXPECT: ^WARNING: No LTL outcome seen; the property was not checked$
// EXPECT: ^VERIFICATION UNKNOWN$
