// A terminating, doubly-recursive function. It has a reachable base case
// (n < 2), so exceeding the unwind bound is a k-bound limitation, not a
// weakness: the comment stays "recursion unwinding assertion" and no CWE is
// emitted. Locks in the soundness contract for branching recursion.
int fib(int n)
{
  if (n < 2)
    return n;
  return fib(n - 1) + fib(n - 2);
}

int main(void)
{
  return fib(20);
}
// Imported from ESBMC regression/esbmc/cwe_recursion_fibonacci_unmapped
// RUN: --unwind 4
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^  recursion unwinding assertion$
// EXPECT: \A(?![\s\S]*CWE)[\s\S]*\Z
