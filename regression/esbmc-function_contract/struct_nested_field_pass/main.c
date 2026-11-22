/* struct_nested_field_pass:
 * Entity contains an embedded Inner struct (pos.x, pos.y) and a scalar flag.
 * Contract: ensures pos.x, pos.y, and flags are set correctly.
 * Body is correct.
 *
 * Expected: VERIFICATION SUCCESSFUL
 */
#include <stddef.h>

typedef struct
{
  int x;
  int y;
} Inner;

typedef struct
{
  Inner pos;
  int flags;
} Entity;

void set_entity(Entity *e, int x, int y, int f)
{
  __ESBMC_requires(__ESBMC_is_fresh(e, sizeof(*e)));
  __ESBMC_requires(e != NULL);
  __ESBMC_ensures(e->pos.x == x && e->pos.y == y);
  __ESBMC_ensures(e->flags == f);
  e->pos.x = x;
  e->pos.y = y;
  e->flags = f;
}

int main() { return 0; }
// Imported from ESBMC regression/function_contract/struct_nested_field_pass
// Needs: --enforce-contract set_entity
// RUN: --enforce-contract set_entity --function set_entity
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
