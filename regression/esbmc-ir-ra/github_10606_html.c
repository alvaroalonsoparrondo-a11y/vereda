unsigned __VERIFIER_nondet_uint(void);

int main(void)
{
  unsigned n = __VERIFIER_nondet_uint();
  __VERIFIER_assert(n >= 0); // an unsigned is never negative
  return 0;
}
// Imported from ESBMC regression/ir-ra/github_10606_html
// Needs: --ir --generate-html-report CHECK_FILE report-1.html contains <td>n = -1</td> CHECK_FILE report-1.html absent n = 4294967295
// RUN: --ir --z3 --generate-html-report
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
