/* struct_return_ptr_field_pass:
 * Struct contains a pointer field (data) and a scalar (size).
 * Contract: ensures both fields match the arguments.
 * Body is correct.
 *
 * Expected: VERIFICATION SUCCESSFUL
 */
#include <stddef.h>

typedef struct
{
  int *data;
  int size;
} Buf;

void init_buf(Buf *b, int *d, int sz)
{
  __ESBMC_requires(__ESBMC_is_fresh(b, sizeof(*b)));
  __ESBMC_requires(b != NULL && d != NULL && sz > 0);
  __ESBMC_ensures(b->data == d);
  __ESBMC_ensures(b->size == sz);
  b->data = d;
  b->size = sz;
}

int main() { return 0; }
// Imported from ESBMC regression/function_contract/struct_return_ptr_field_pass
// Needs: --enforce-contract init_buf
// RUN: --enforce-contract init_buf --function init_buf
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
