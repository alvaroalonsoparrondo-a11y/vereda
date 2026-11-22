int add(int a, int b) {
  return a + b;
}

int multiply(int x, int y) {
  return x * y;
}

int main() {
  int p = 1, q = 2, r = 3;
  int sum = add(p, q);
  int prod = multiply(sum, r);
  int result = add(prod, multiply(p, r));
  return result;
}
// Imported from ESBMC regression/esbmc/print-function-deps_1
// Needs: --show-call-sites
// RUN: --show-call-sites
// MODE: FUTURE
// EXPECT: ^c:@F@main -> c:@F@add\(p, q\) \[.*main\.c:\d+\]$
// EXPECT: ^c:@F@main -> c:@F@multiply\(sum, r\) \[.*main\.c:\d+\]$
// EXPECT: ^c:@F@main -> c:@F@multiply\(p, r\) \[.*main\.c:\d+\]$
// EXPECT: ^c:@F@main -> c:@F@add\(prod, return_value.*\) \[.*main\.c:\d+\]$
// EXPECT: ^__ESBMC_main -> c:@F@main\(\) \[.*main\.c:\d+\]$
