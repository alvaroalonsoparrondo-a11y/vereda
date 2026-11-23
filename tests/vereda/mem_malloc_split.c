// A malloc result is ite(ok, object, null). After a null check the path
// picks the object, so a size read through it is constant; without one,
// writes reach both sides and read back the same.
// EXPECT: ^Violated property:\n  file \S*mem_malloc_split\.c line 32 column 3 function main\n  __VERIFIER_assert\n  b\[3\] == 0$
// EXPECT: ^VERIFICATION FAILED$
extern void __VERIFIER_assert(int);
void *malloc(unsigned long);
void *memset(void *, int, unsigned long);

struct table {
  int n;
  int *buckets;
};

int main(void) {
  struct table *u = malloc(sizeof *u); // unchecked
  u->n = 2;
  __VERIFIER_assert(u->n == 2);

  struct table *t = malloc(sizeof *t);
  if (!t)
    return 0;
  t->n = 4;
  int *b = malloc(t->n * sizeof(int));
  if (!b)
    return 0;
  memset(b, 0, t->n * sizeof(int));
  t->buckets = b;
  t->buckets[3] = 7;
  __VERIFIER_assert(b[0] == 0 && t->buckets[3] == 7);
  __VERIFIER_assert(u->n == 2);
  __VERIFIER_assert(b[3] == 0);
  return 0;
}
