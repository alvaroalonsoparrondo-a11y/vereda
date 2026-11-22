
int main()
{
	if(nondet_bool())
		__ESBMC_unreachable();
}
// Imported from ESBMC regression/esbmc/unreachable-true-off
// EXPECT: ^VERIFICATION SUCCESSFUL$
