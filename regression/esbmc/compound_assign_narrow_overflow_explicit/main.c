/* Control for compound_assign_narrow_overflow: the same program written in the
   long form the standard says `b += a` is equivalent to. This one is already
   caught, so a fix that stops reporting the overflow here cannot pass the pair. */
char b;

int main()
{
  b = 3;
  int a = 2147483647;
  b = b + a;
  return 0;
}
// Imported from ESBMC regression/esbmc/compound_assign_narrow_overflow_explicit
// Needs: --overflow-check
// RUN: --overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION FAILED$
