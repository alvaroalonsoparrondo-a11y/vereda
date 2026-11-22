int nondet_int(void);
int mid(int lo, int hi) { return lo + (hi - lo) / 2; }
int main(void) {
  int lo = nondet_int(), hi = nondet_int();
  __VERIFIER_assume(lo <= hi);
  int m = mid(lo, hi);
  __VERIFIER_assert(lo <= m && m <= hi); // midpoint in range
  return 0;
}
// Imported from ESBMC regression/goto2lean/int_mode_midpoint
// Needs: --goto2lean --ir
// RUN: --goto2lean --ir
// MODE: FUTURE
// EXPECT: ^def mid \(lo : Int\) \(hi : Int\) \(post : Int → Prop\) : Prop :=$
// EXPECT: ^  post \(lo \+ \(Int\.tdiv \(hi - lo\) \(2 : Int\)\)\)$
// EXPECT: ^    show Int\.sign \(2 : Int\) = 1 from rfl\]$
// EXPECT: ^  all_goals \(repeat. split\) <;> \(try simp_all\) <;> omega$
