/* Test: assigns compliance with ctx->field — FAIL
 * Function update_count declares assigns(ctx->count) but also writes ctx->capacity.
 * The unauthorized write to ctx->capacity violates the assigns clause.
 */

typedef struct {
    int count;
    int capacity;
} queue_t;

void update_count(queue_t *ctx)
{
    __ESBMC_assigns(ctx->count);

    ctx->count = ctx->count + 1;
    ctx->capacity = 0;  /* VIOLATION: capacity not in assigns clause */
}

int main()
{
    queue_t q;
    q.count = 0;
    q.capacity = 10;
    update_count(&q);
    return 0;
}
// Imported from ESBMC regression/function_contract/assigns_ptr_field_compliance_fail
// Needs: --enforce-contract update_count
// RUN: --enforce-contract update_count
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
