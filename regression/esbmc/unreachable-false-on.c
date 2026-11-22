
int main()
{
	if(0)
		__ESBMC_unreachable();
}
// Imported from ESBMC regression/esbmc/unreachable-false-on
// Needs: --enable-unreachability-intrinsic
// RUN: --enable-unreachability-intrinsic
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
