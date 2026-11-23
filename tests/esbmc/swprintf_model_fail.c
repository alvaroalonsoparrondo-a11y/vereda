// Anti-vacuity twin of swprintf_model: the model over-approximates, so the
// contents are unconstrained and cannot be pinned to a particular string.
#include <wchar.h>
#include <assert.h>

int main(void)
{
  wchar_t buf[8];
  int r = swprintf(buf, 8, L"%d", 42);
  if (r >= 0)
    assert(buf[0] == L'4');
  return 0;
}
// Imported from ESBMC regression/esbmc/swprintf_model_fail
// RUN: --unwind 10 --no-unwinding-assertions
// EXPECT: ^VERIFICATION FAILED$
