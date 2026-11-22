/* mem_struct_init_fail:
 * Same contract.  Body forgets to initialise v->z (leaves it nondet).
 * ensures(v->z == z) catches the missing initialisation.
 *
 * Expected: VERIFICATION FAILED
 */
#include <stddef.h>

typedef struct { int x; int y; int z; } Vec3;

void vec3_init(Vec3 *v, int x, int y, int z)
{
  __ESBMC_requires(__ESBMC_is_fresh(v, sizeof(*v)));
  __ESBMC_requires(v != NULL);
  __ESBMC_ensures(v->x == x && v->y == y && v->z == z);
  v->x = x;
  v->y = y;
  /* BUG: v->z is never written — remains nondet */
}

int main() { return 0; }
// Imported from ESBMC regression/function_contract/mem_struct_init_fail
// Needs: --enforce-contract vec3_init
// RUN: --enforce-contract vec3_init --function vec3_init
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
