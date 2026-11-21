// A defined reach_error is an ordinary call, as in ESBMC's default. Walking
// into it needs calls, so this stays FUTURE; the failure must then be
// reported inside the body, at __assert_fail.
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: ^Violated property:\n  file \S*reach_error_body\.c line 10 column 25 function reach_error\n  __assert_fail$
extern void __assert_fail(const char *, const char *, unsigned, const char *);
extern int __VERIFIER_nondet_int(void);
void reach_error(void) { __assert_fail("0", "reach_error_body.c", 10, "reach_error"); }

int main(void) {
  if (__VERIFIER_nondet_int() == 7)
    reach_error();
  return 0;
}
