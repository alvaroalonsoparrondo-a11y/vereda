#include <stdio.h>
#include <string.h>

char global_arr[10];

char __VERIFIER_nondet_char();

void __VERIFIER_nondet_init_arr(char *arr)
{
  unsigned int i = 0;
  for(; i < 9; i++)
    arr[i] = __VERIFIER_nondet_char();
}

void global_fun()
{
  __VERIFIER_nondet_init_arr(global_arr);
  unsigned int len = strlen(global_arr);
  __VERIFIER_assert(len == 0); // Error: array must be empty
}

int main()
{
  global_fun();
  return 0;
}
// Imported from ESBMC regression/esbmc/github_371_2
// RUN: --no-unwinding-assertions --unwind 12
// EXPECT: ^VERIFICATION FAILED$
