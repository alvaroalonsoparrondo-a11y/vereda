#include<stdlib.h>
#include<stdio.h>

struct list_el {
   struct list_el * next;
};

typedef struct list_el item;


int main(void) {
  item *curr, *head, *ret;
  int i;

  head = NULL;

  curr = (item *)malloc(sizeof(item));
  __ESBMC_assume(curr);
  curr->next  = head;

  while(curr) {
    curr = curr->next;
  }

	return 0;
}
// Imported from ESBMC regression/cbmc/01_cbmc_Malloc15
// RUN: --unwind 2
// EXPECT: ^VERIFICATION SUCCESSFUL$
// Vereda: unmet EXPECT: ^VERIFICATION SUCCESSFUL$
// MODE: FUTURE
