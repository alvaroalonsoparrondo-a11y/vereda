unsigned __VERIFIER_nondet_uint(void);

int main(void)
{
  unsigned n = __VERIFIER_nondet_uint();
  __VERIFIER_assert(n >= 0); // an unsigned is never negative
  return 0;
}
// Imported from ESBMC regression/ir-ra/github_10606_json
// Needs: --ir --generate-json-report CHECK_FILE report.json contains "value": "-1" CHECK_FILE report.json absent "value": "4294967295"
// RUN: --ir --z3 --generate-json-report
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
