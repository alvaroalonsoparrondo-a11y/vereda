int s;

int main()
{
	s = 0;
	s = 1;
	s = 0;
	return 0;
}
// Imported from ESBMC regression/ltl/github_6582_no_ltl
// RUN: -DLTL_PREFIX_BOUND=6
// FILES: safety.c
// EXPECT: ^WARNING: monitor has no __ESBMC_switch_from_monitor\(\) call; regenerate it with
// EXPECT: ^VERIFICATION SUCCESSFUL$
// Vereda: unmet EXPECT: ^WARNING: monitor has no __ESBMC_switch_from_monitor\(\) call; regenerate it with
// MODE: FUTURE
