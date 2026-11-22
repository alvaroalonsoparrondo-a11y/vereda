
int main()
{
	if(nondet_bool())
		reach_error();
}
// Imported from ESBMC regression/esbmc/unreachable-true-on
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: \breachability: unreachable code reached\b
// Vereda: unmet EXPECT: \breachability: unreachable code reached\b
// MODE: FUTURE
