#include <assert.h>

int nondet_int(void);

struct S
{
  int a;
  int b;
};

struct S make(int x)
{
  struct S r;
  r.a = 1;
  r.b = x + 1;
  return r;
}

int main(void)
{
  int x = nondet_int();
  struct S s;
  struct S *p = &s;
  *p = make(x);
  assert(s.a == 1);
  assert(s.b == x);
  return 0;
}
// Imported from ESBMC regression/esbmc/field_sensitive_ssa_opaque_whole_read_fail
// Needs: --field-sensitive-ssa
// RUN: --field-sensitive-ssa
// MODE: FUTURE
// EXPECT: ^Field-sensitive SSA splits 1 struct object\(s\)$
// EXPECT: ^VERIFICATION FAILED$
