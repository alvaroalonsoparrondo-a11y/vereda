// Globals with initialisers, including one that points into another global.
// EXPECT: ^VERIFICATION SUCCESSFUL$
extern void __VERIFIER_assert(int);

int table[3] = {1, 2, 3};
int *second = &table[1];
struct { int n; int *items; } box = {3, table};
int zeroed[5];

int main(void) {
  *second = 20;
  __VERIFIER_assert(table[1] == 20 && box.items[2] == 3 && box.n == 3 && zeroed[4] == 0);
  return 0;
}
