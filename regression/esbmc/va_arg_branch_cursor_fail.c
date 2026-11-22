#include <assert.h>
#include <stdarg.h>

int __VERIFIER_nondet_int(void);

int branch(int c, ...)
{
  va_list ap;
  va_start(ap, c);
  int a = 0;
  if (c)
    a = va_arg(ap, int);
  int b = va_arg(ap, int);
  va_end(ap);
  return a * 10 + b;
}

int ternary(int c, ...)
{
  va_list ap;
  va_start(ap, c);
  int a = c ? va_arg(ap, int) : 0;
  int b = va_arg(ap, int);
  va_end(ap);
  return a * 10 + b;
}

int main(void)
{
  int c = __VERIFIER_nondet_int();
  assert(branch(c, 1, 2) == (c ? 12 : 2));
  assert(ternary(c, 1, 2) == (c ? 12 : 2));
  return 0;
}
// Imported from ESBMC regression/esbmc/va_arg_branch_cursor_fail
// RUN: --multi-property
// EXPECT: ^  FAILED +\[main\.assertion\.1\] +line 31  assertion branch\(c, 1, 2\) == \(c \? 12 : 2\)$
// EXPECT: ^  FAILED +\[main\.assertion\.2\] +line 32  assertion ternary\(c, 1, 2\) == \(c \? 12 : 2\)$
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^  FAILED +\[main\.assertion\.1\] +line 31  assertion branch\(c, 1, 2\) == \(c \? 12 : 2\)$
// MODE: FUTURE
