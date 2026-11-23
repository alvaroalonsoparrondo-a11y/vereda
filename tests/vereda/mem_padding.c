// Static storage zeroes struct padding, so reading it through a char
// pointer gives 0.
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern void __VERIFIER_assert(int);

struct padded {
  char c;
  int i;
};
struct padded g = {'x', 5};

int main(void) {
  unsigned char *bytes = (unsigned char *)&g;
  __VERIFIER_assert(bytes[0] == 'x' && bytes[1] == 0 && bytes[3] == 0 && g.i == 5);
  return 0;
}
