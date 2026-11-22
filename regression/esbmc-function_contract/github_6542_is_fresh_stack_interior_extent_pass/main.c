/* github_6542_is_fresh_stack_interior_extent_pass:
 * The positive half of the interior-pointer boundary. &v.coeffs[2] sits 8
 * bytes into a 16-byte object, so a request for exactly the 8 that remain is
 * discharged. github_6542_is_fresh_stack_interior_extent_fail asks for 16 and
 * must not be. */
typedef struct { int coeffs[4]; } P;

void callee(int *p) {
  __ESBMC_requires(__ESBMC_is_fresh(p, 8));
  __ESBMC_assigns(p[0]);
  __ESBMC_ensures(p[0] == 1);
  p[0] = 1;
}

int main(void) {
  P v;
  callee(&v.coeffs[2]);
  return 0;
}
// Imported from ESBMC regression/function_contract/github_6542_is_fresh_stack_interior_extent_pass
// Needs: --replace-call-with-contract callee
// RUN: --replace-call-with-contract callee --unwind 8
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
