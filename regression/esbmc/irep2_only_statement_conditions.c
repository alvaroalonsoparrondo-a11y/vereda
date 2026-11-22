/* goto_convert's branch lowering wants a boolean guard; clang leaves an integer
   controlling expression as it is written. */
int nondet_int(void);

int main(void)
{
  int a = nondet_int();
  int b = nondet_int();
  int c = nondet_int();
  int n = 0;

  if (a)
    n++;

  while (b)
    b = 0;

  for (; c;)
    c = 0;

  return n;
}
// Imported from ESBMC regression/esbmc/irep2_only_statement_conditions
// Needs: --goto-functions-only --clang-c-irep2-adjust-only
// RUN: --goto-functions-only --clang-c-irep2-adjust-only
// MODE: FUTURE
// EXPECT: IF !\(_Bool\)a THEN GOTO
// EXPECT: IF !\(_Bool\)b THEN GOTO
// EXPECT: IF !\(_Bool\)c THEN GOTO
