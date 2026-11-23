// A recursive function that fully terminates within the unwind bound. No
// unwinding assertion is reached, so verification succeeds and no CWE is
// emitted. Guards against the uncontrolled-recursion detector ever firing
// on a well-behaved, terminating recursion.
int f(int n)
{
  if (n <= 0)
    return 0;
  return f(n - 1);
}

int main(void)
{
  return f(3);
}
// Imported from ESBMC regression/esbmc/cwe_recursion_bounded_ok
// RUN: --unwind 8
// EXPECT: ^VERIFICATION SUCCESSFUL$
// EXPECT: \A(?![\s\S]*CWE)[\s\S]*\Z
// EXPECT: \A(?![\s\S]*recursion unwinding assertion)[\s\S]*\Z
