/* Soundness companion: the function writes b->coeffs[0], which is NOT in the
 * assigns clause. The Phase 2C array-field frame check (nondet witness index)
 * must catch it -> VERIFICATION FAILED. Confirms the fix is sound, not merely
 * crash-avoiding. */
#include <stdint.h>
#include <stddef.h>
#define N 8
typedef struct { int16_t coeffs[N]; } poly;
void add(poly *r, poly *b)
{
  __ESBMC_requires(__ESBMC_is_fresh(r, sizeof(*r)));
  __ESBMC_requires(__ESBMC_is_fresh(b, sizeof(*b)));
  __ESBMC_requires(r != NULL && b != NULL);
  __ESBMC_assigns(r->coeffs);
  __ESBMC_ensures(1);
  for (unsigned i = 0; i < N; i++)
    r->coeffs[i] = (int16_t)(r->coeffs[i] + b->coeffs[i]);
  b->coeffs[0] = 42; /* illegal: b->coeffs not in assigns clause */
}
// Imported from ESBMC regression/function_contract/enforce_ptr_param_array_field_fail
// Needs: --enforce-contract add
// RUN: --enforce-contract add --function add --unwind 9
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
