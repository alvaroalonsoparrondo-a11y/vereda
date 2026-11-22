unsigned nondet_uint(void);
int main(void){ unsigned _ = nondet_uint(); __ESBMC_assert(_ == _, "k"); return 0; }
// Imported from ESBMC regression/goto2lean/keyword_identifier
// Needs: --goto2lean
// RUN: --goto2lean
// MODE: FUTURE
// EXPECT: ^  ∀ «_» : BitVec 32,$
// EXPECT: ^  \(«_» = «_»\) ∧ \($
