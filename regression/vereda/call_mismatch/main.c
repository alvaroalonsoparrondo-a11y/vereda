// A declaration that disagrees with the definition in another file: the
// walker names the mismatch instead of calling it an indirect call.
// FILES: g.c
// EXPECT: ^VERIFICATION UNKNOWN: unsupported: call to g with a mismatched signature at file \S*main\.c line 7
int g(long a);

int main(void) { return g(1); }
