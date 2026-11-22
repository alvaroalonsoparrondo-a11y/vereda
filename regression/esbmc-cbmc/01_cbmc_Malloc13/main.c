#include <stdio.h>

struct list_el {
  int val;
  struct list_el *next;
};

typedef struct list_el item;

int main()
{
  item *curr, *head;

  head = NULL;

  curr = (item *)malloc(sizeof(item));
  __ESBMC_assume(curr);
  curr->val = 1;
  curr->next  = head;
  head = curr;

  curr = (item *)malloc(sizeof(item));
  __ESBMC_assume(curr);
  curr->val = 2;
  curr->next  = head;
  head = curr;

  assert(head->val==1);

}
// Imported from ESBMC regression/cbmc/01_cbmc_Malloc13
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^VERIFICATION FAILED$
// MODE: FUTURE
