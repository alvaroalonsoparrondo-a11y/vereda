// A pointer walking a[2][3] as flat memory, with the loop exit spelled
// &a[1][2]. Both sides have to reduce to an offset off &a[0][0] for the guard
// to be decided syntactically; without that the same program with no --unwind
// runs forever (#6778).
#include <assert.h>

int main(void)
{
  int a[2][3] = {{1, 2, 3}, {4, 5, 6}};
  int sum = 0;

  for (int *p = &a[0][0]; p != &a[1][2]; ++p)
    sum += *p;

  assert(sum == 15);
  return 0;
}
// Imported from ESBMC regression/esbmc/addressof_multidim_bound
// EXPECT: ^VERIFICATION SUCCESSFUL$
// EXPECT: ^Generated [0-9]+ VCC\(s\), 1 remaining after simplification
// EXPECT: assertion sum == 15
// Vereda: unmet EXPECT: ^Generated [0-9]+ VCC\(s\), 1 remaining after simplification
// MODE: FUTURE
