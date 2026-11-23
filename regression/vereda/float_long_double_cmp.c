// Comparing long doubles needs their x86_fp80 format, which is not an IEEE
// interchange format: unsupported, not a crash.
// RUN: -m64
// EXPECT: ^VERIFICATION UNKNOWN: unsupported: type x86_fp80$
extern long double a, b;
int main(void) { return a < b; }
