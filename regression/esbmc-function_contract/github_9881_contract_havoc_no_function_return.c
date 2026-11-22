/* #9881: a call replaced by its contract havocs g at the call's location. That
 * is not a value a call returned, so it gets no function_return waypoint. */
extern int __VERIFIER_nondet_int(void);

int g;

void set_g(void)
{
  __ESBMC_assigns(g);
  __ESBMC_ensures(g == 42);
  g = 42;
}

int main(void)
{
  int n = __VERIFIER_nondet_int();
  set_g();
  __VERIFIER_assert(n + g != 47); // n is 5
}
// Imported from ESBMC regression/function_contract/github_9881_contract_havoc_no_function_return
// Needs: --replace-call-with-contract * --witness-output-yaml -
// RUN: --replace-call-with-contract "*" --witness-output-yaml -
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: value: "\\\\result == 5"\n.*\n.*\n.*\n *line: 16\n *column: 33$
// EXPECT: (?s)\A(?!.*result == 42)
