#ifndef uint16_t
#define uint16_t unsigned short
#endif
int main()
{
  uint16_t a = 0xFFFF;
  uint16_t b = a << 16;
  return 0;
}
// Imported from ESBMC regression/esbmc/github_381
// Needs: --overflow-check
// RUN: --overflow-check
// MODE: FUTURE
// EXPECT: github_381\.c line 7 column 3 function main$
