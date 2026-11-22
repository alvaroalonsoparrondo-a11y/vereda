#include <assert.h>
#include <stdint.h>

int main()
{
  int d = nondet_int();
  int c = nondet_int();
  char e = nondet_char();

  // Cast on one side breaks canonical cancellation form
  assert(((d + c) == (d + (int)e)) ? (c == (int)e) : 1);

  return 0;
}

// Imported from ESBMC regression/esbmc/simplifier15
// EXPECT: ^VERIFICATION SUCCESSFUL$
