char __VERIFIER_nondet_char();

void init_loop(void *base, unsigned int size) {
  for (int i = 0; i < size; i++) {
    *((char *)base + i) = __VERIFIER_nondet_char();
  }
}

typedef struct my_obj {
  int foo;
  void *bar;
} obj;

int some_var;

int main() {
  obj bug;
  init_loop(&bug, sizeof(bug));
  __VERIFIER_assume(bug.bar == &some_var);
  __VERIFIER_assert(0); // this should be reachable
}
// Imported from ESBMC regression/esbmc/github_2153_5
// RUN: --no-unwinding-assertions --unwind 24
// EXPECT: ^VERIFICATION FAILED$
