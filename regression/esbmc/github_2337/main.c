int a, b;
void main() { -(a < b); }
// Imported from ESBMC regression/esbmc/github_2337
// Needs: --overflow-check
// RUN: --overflow-check
// MODE: FUTURE
// EXPECT: ^VERIFICATION SUCCESSFUL$
