/* Two bound checks share a description and a position; each needs its own
   row (esbmc/esbmc#7900). */
int a[4];
int main()
{
  unsigned i = nondet_uint(), j = nondet_uint();
  __ESBMC_assume(i < 4);
  int s = a[i] + a[j];
  return s;
}
// Imported from ESBMC regression/esbmc/multi_property_same_position_asserts
// RUN: --multi-property
// EXPECT: ^\s+PASSED\s+\[main\.array-bounds-violated\.\d+\]\s+line\s+8\s+array bounds violated: array `a' upper bound \[\([^)]*\)i < 4\]$
// EXPECT: ^\s+FAILED\s+\[main\.array-bounds-violated\.\d+\]\s+line\s+8\s+array bounds violated: array `a' upper bound \[\([^)]*\)j < 4\]$
// EXPECT: ^\*\* 1 of 2 properties failed, 1 passed$
// EXPECT: ^VERIFICATION FAILED$
// Vereda: unmet EXPECT: ^\s+PASSED\s+\[main\.array-bounds-violated\.\d+\]\s+line\s+8\s+array bounds violated: array `a' upper bound \[\([^)]*\)i < 4\]$
// MODE: FUTURE
