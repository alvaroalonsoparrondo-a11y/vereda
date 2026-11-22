int main()
{
	int tt = nondet_int();
	int res = tt + 1;
	int a = res > 1 ? res / 2 : res;
	__ESBMC_assert(a == 2, "Failed as expected");
}
// Imported from ESBMC regression/esbmc/github_447-1
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: \bFailed as expected\b
// Vereda: unmet EXPECT: ^VERIFICATION FAILED$
// MODE: FUTURE
