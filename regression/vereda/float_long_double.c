// long double is x86_fp80, not an IEEE interchange format: unsupported, even
// when only its class is tested, rather than a crash.
// RUN: -m64
// EXPECT: ^VERIFICATION UNKNOWN: unsupported: type x86_fp80$
#include <math.h>
static long double g;
int main(void) { return isnan(g); }
