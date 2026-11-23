/* #9937: writing a member of a union whose other member holds an
 * out-of-bounds pointer must not make the path vacuous. */
int main()
{
  union
  {
    int *p;
    struct
    {
      int *a;
      long c;
    } s;
  } u;
  int arr[2];
  u.p = arr + 100;
  u.s.c = 4;
  __VERIFIER_assert(u.s.c != 4); // reachable
}
// Imported from ESBMC regression/esbmc/github_9937_fail
// EXPECT: ^VERIFICATION FAILED$
// EXPECT: \[main.assertion.1\]  line 17  reachable
// EXPECT: ^  u\.s\.c != 4$
// Vereda: unmet EXPECT: \[main.assertion.1\]  line 17  reachable
// MODE: FUTURE
