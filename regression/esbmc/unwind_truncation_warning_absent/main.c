// Control: the same loop with a bound that covers it. Nothing is truncated,
// so the warning must not appear.
#include <assert.h>

int main(void)
{
  int s = 0;
  for (int i = 0; i < 10; i++)
    s++;
  assert(s == 10);
  return 0;
}
// Imported from ESBMC regression/esbmc/unwind_truncation_warning_absent
// RUN: --unwind 11 --no-unwinding-assertions
// EXPECT: ^VERIFICATION SUCCESSFUL$
// EXPECT: \A(?!(.|\n)*the unwinding bound cut a loop short)
