// A pointer rebuilt from an integer still reaches its object, as in ESBMC
// #9785: stores through it are seen by loads through the original.
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern int __VERIFIER_nondet_int(void);
extern void __VERIFIER_assume(int);
extern void __VERIFIER_assert(int);

struct port {
  unsigned a0, a1, a2, a3;
  void *d0;
};
static struct port ports[2];
int g;

int main(void) {
  int i = __VERIFIER_nondet_int();
  __VERIFIER_assume(i == 0 || i == 1);
  unsigned long base = (unsigned long)ports + i * sizeof(struct port);
  *(unsigned *)(base + 8) = 5u;
  *(void **)(base + 16) = &g;
  __VERIFIER_assert(ports[i].a2 == 5u && ports[i].d0 == &g);
  return 0;
}
