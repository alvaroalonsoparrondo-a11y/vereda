// Fields of different widths written through a pointer to a struct, and a
// pointer stored in memory and loaded back.
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern void __VERIFIER_assert(int);

struct s {
  char c;
  short h;
  long l;
  int *p;
};

static void fill(struct s *x, int *target) {
  x->c = 'a';
  x->h = -2;
  x->l = 1L << 40;
  x->p = target;
}

int main(void) {
  int v = 7;
  struct s x;
  fill(&x, &v);
  *x.p = 9;
  int **pp = &x.p;
  __VERIFIER_assert(x.c == 'a' && x.h == -2 && x.l == 1L << 40 && v == 9 && **pp == 9);
  return 0;
}
