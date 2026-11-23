// GCC vectors: a global vector initialiser in memory, element-wise
// operations split by the scalarizer, and a variable index.
// RUN: --unwind 5
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern void __VERIFIER_assert(int);
extern unsigned __VERIFIER_nondet_uint(void);
typedef int v4si __attribute__((__vector_size__(16)));
typedef float v4sf __attribute__((__vector_size__(16)));
v4si g = {1, 2, 3, 4};
v4sf h = {0.5f, 1.5f, -2.0f, 8.0f};
int main(void) {
  g = g * 2 + 1;
  for (int i = 0; i < 4; i++)
    __VERIFIER_assert(g[i] == 2 * (i + 1) + 1);
  unsigned k = __VERIFIER_nondet_uint() % 4;
  v4sf d = h * 2;
  __VERIFIER_assert(d[k] == h[k] + h[k]);
  return 0;
}
