// Models of <math.h> classification functions, for calls that bypass the
// macros (a call without <math.h> passes a double). C17 7.12.3.
int isnan(double x) { return x != x; }
int isinf(double x) { return x == __builtin_inf() || x == -__builtin_inf(); }
int isfinite(double x) { return !isnan(x) && !isinf(x); }
int signbit(double x) { return __builtin_signbit(x); }
