int s;

int main()
{
	s = 0;
	s = 1;
	s = 0;
	return 0;
}
// Imported from ESBMC regression/ltl/github_6546
// Needs: --ltl
// RUN: --ltl safety.c -DLTL_PREFIX_BOUND=6
// FILES: safety.c
// MODE: FUTURE
// EXPECT: ^Final lowest outcome: LTL_BAD$
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: \A(?![\s\S]*monitor has no __ESBMC_switch_from_monitor)[\s\S]*\Z
