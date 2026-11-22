// example.c

/* Two departures from the issue's verbatim reproducer, both for portability:
 *
 * - It read uninitialised locals, which is undefined behaviour; nondet_int()
 *   states the "arbitrary value" intent directly.
 * - It used assert(). MSVC's assert.h puts the failure path under !(cond), so
 *   with `__ESBMC_assume(c < 100)` right above it that path is unsatisfiable
 *   and coverage correctly reports the assertion UNREACHED -- a different
 *   answer from the same source on Linux/macOS, where assert() lowers to an
 *   unconditional check. __ESBMC_assert is unconditional on every target.
 */

int main()
{
  int x = nondet_int();
  int y = nondet_int();

  __ESBMC_assume(x < 100);
  __ESBMC_assume(x > 0);

  __ESBMC_assume(y < 100);
  __ESBMC_assume(y > 0);

  int c = x + y;

  __ESBMC_assume(c < 100);
  __ESBMC_assert(c < 100, "c < 100");

  return c;
}
// Imported from ESBMC regression/esbmc/github_2163
// Needs: --assertion-coverage-claims
// RUN: --assertion-coverage-claims
// MODE: FUTURE
// EXPECT: Assertion Instances Coverage: 100%
// EXPECT: : REACHED$
// EXPECT: ^COVERAGE ANALYSIS COMPLETE$
