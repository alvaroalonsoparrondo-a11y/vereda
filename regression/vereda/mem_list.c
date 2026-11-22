// A heap linked list built and traversed in loops.
// RUN: --unwind 4 --force-malloc-success
// EXPECT: ^VERIFICATION SUCCESSFUL$
#include <stdlib.h>
extern void __VERIFIER_assert(int);

struct node {
  int value;
  struct node *next;
};

int main(void) {
  struct node *head = 0;
  for (int i = 1; i <= 3; i++) {
    struct node *n = malloc(sizeof *n);
    n->value = i;
    n->next = head;
    head = n;
  }
  int sum = 0;
  for (struct node *n = head; n; n = n->next)
    sum += n->value;
  __VERIFIER_assert(sum == 6 && head->value == 3);
  return 0;
}
