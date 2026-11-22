
int main()
{
	if(nondet_bool())
		__ESBMC_unreachable();
}
// Imported from ESBMC regression/esbmc/unreachable-true-on
// Needs: --enable-unreachability-intrinsic
// RUN: --enable-unreachability-intrinsic
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: \breachability: unreachable code reached\b
